/*  CURSES GAMES, a selection of Unix terminal games.
 *  Copyright (C) 2021 Paul Griffiths.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/select.h>

#include "tge.h"
#include "util.h"

static struct tge_parameters game_param;
static void tge_game_loop(void);

int
tge_begin_game(const struct tge_parameters * parameters) {
    game_param.setup_function = parameters->setup_function;
    game_param.draw_function = parameters->draw_function;
    game_param.input_function = parameters->input_function;
    game_param.teardown_function = parameters->teardown_function;
    game_param.timer_interval = parameters->timer_interval;

    /*  Initialize PRNG and game  */
    srand((unsigned)time(NULL));
    tge_start_game();
    tge_set_signal_handlers();
    tge_initialize_screen();
    game_param.setup_function();
    tge_timer_start(game_param.timer_interval, game_param.timer_interval);

    /*  Enter main game loop  */
    tge_game_loop();

    /*  Clean up and exit game  */
    tge_timer_stop();
    int end_status = tge_end_status();
    game_param.teardown_function(end_status);
    tge_free_screen();

    return end_status;
}

static void tge_game_loop(void) {
    sigset_t unblocked, blocked, oldmask;

    /*  Store current mask in both blocked and unblocked,
     *  and block SIGALRM in blocked, but unblock SIGALRM
     *  in unblocked. These masks are used in the pselect()
     *  call below, see comment in main game loop.           */
    if ( sigprocmask(SIG_BLOCK, NULL, &oldmask) == -1 ) {
        x_perror("sigprocmask failed");
    }

    if ( sigprocmask(SIG_BLOCK, NULL, &unblocked) == -1 ) {
        x_perror("sigprocmask failed");
    }

    if ( sigprocmask(SIG_BLOCK, NULL, &blocked) == -1 ) {
        x_perror("sigprocmask failed");
    }

    if ( sigaddset(&blocked, SIGALRM) == -1 ) {
        x_perror("sigaddset failed");
    }

    if ( sigdelset(&unblocked, SIGALRM) == -1 ) {
        x_perror("sigdelset failed");
    }

    /*  Block SIGALRM prior to entering main loop  */
    if ( sigprocmask(SIG_BLOCK, &blocked, NULL) == -1 ) {
        x_perror("sigprocmask failed");
    }

    while ( !tge_game_ended() ) {
        if ( tge_needs_refresh() ) {
            tge_set_needs_refresh(false);
            game_param.draw_function();
        }

        /* 
         * NOTE: If SIGALRM is triggered after the preceding
         * check of tge_needs_refresh(), but before the following
         * select() call, then it is possible one screen update
         * may effectively be "skipped" if no input is entered, since
         * select() will block until the next SIGLARM. Two updates in
         * a row cannot be skipped in this manner, since we check
         * tge_needs_refresh() at the start of every iteration of the
         * loop.
         * 
         * To avoid this, we block SIGALRM prior to entering the loop,
         * and call pselect() instead of select(), to atomically
         * unblock SIGALRM. Any pending signal will be delivered
         * immediately, and pselect() will return. 
         */
        fd_set fs;
        FD_ZERO(&fs);
        FD_SET(STDIN_FILENO, &fs);
        int status = pselect(STDIN_FILENO + 1, &fs,
                             NULL, NULL, NULL, &unblocked);
        if ( status == -1 ) {
            if ( errno == EINTR ) {
                /*  Do nothing if interrupted by signal, and
                 *  just proceed to next iteration of loop where
                 *  tge_needs_refresh() will be immediately checked.  */
            }
            else {

                /*  Exit on any other error from select()  */
                x_perror("select failed");
            }
        }
        else {
            /*  select() showed input ready, so fetch and handle it  */
            int c = tge_get_character();
            game_param.input_function(c);
        }
    }

    /*  Restore original signal mask  */
    if ( sigprocmask(SIG_BLOCK, &oldmask, NULL) == -1 ) {
        x_perror("sigprocmask failed");
    }
}


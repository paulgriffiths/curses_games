/*!
 * \file            tge_main_game.c
 * \brief           Implementation of TGE main game functions.
 * \details         Implementation of TGE main game functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include "tge.h"

/*!  File scope variable for game parameters  */
static struct tge_parameters game_param;

/*!
 * \brief       Main game loop function.
 * \details     Main game loop function.
 */
static void tge_game_loop(void);

int tge_begin_game(const struct tge_parameters * parameters) {
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
         * loop. This is not the end of the world, but could lead to
         * the (very) occasional unexpected stutter in the game. There
         * appears to be no good way to prevent this, other than to
         * minimize the amount of time between the two calls.
         */

        fd_set fs;
        FD_ZERO(&fs);
        FD_SET(STDIN_FILENO, &fs);
        int status = select(STDIN_FILENO + 1, &fs, NULL, NULL, NULL);
        if ( status == -1 ) {
            if ( errno == EINTR ) {

                /*  Do nothing if interrupted by signal, and
                 *  just proceed to next iteration of loop where
                 *  tge_needs_refresh() will be immediately checked.  */
            }
            else {

                /*  Exit on any other error from select()  */

                perror("worms: error from select()");
                exit(EXIT_FAILURE);
            }
        }
        else {

            /*  select() showed input ready, so fetch and handle it  */

            int c = tge_get_character();
            game_param.input_function(c);
        }
    }
}


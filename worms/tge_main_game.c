#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include "tge.h"

static void tge_game_loop(void);

static struct tge_parameters game_param;

int tge_begin_game(struct tge_parameters * parameters) {
    game_param.setup_function = parameters->setup_function;
    game_param.draw_function = parameters->draw_function;
    game_param.input_function = parameters->input_function;
    game_param.teardown_function = parameters->teardown_function;
    game_param.timer_interval = parameters->timer_interval;

    srand((unsigned)time(NULL));
    tge_start_game();
    tge_set_signal_handlers();
    tge_initialize_screen();
    game_param.setup_function();
    tge_timer_start(game_param.timer_interval, game_param.timer_interval);
    tge_game_loop();
    tge_timer_stop();
    game_param.teardown_function(tge_end_status());
    tge_free_screen();
    return tge_end_status();
}

static void tge_game_loop(void) {
    while ( !tge_game_ended() ) {
        if ( tge_needs_refresh() ) {
            tge_set_needs_refresh(false);
            game_param.draw_function();
        }

        fd_set fs;
        FD_ZERO(&fs);
        FD_SET(STDIN_FILENO, &fs);
        int status = select(STDIN_FILENO + 1, &fs, NULL, NULL, NULL);
        if ( status == -1 ) {
            if ( errno == EINTR ) {
            }
            else {
                perror("worms: error from select()");
                exit(EXIT_FAILURE);
            }
        }
        else {
            int c = tge_get_character();
            game_param.input_function(c);
        }
    }
}


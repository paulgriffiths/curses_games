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

#include "worms.h"
#include "options.h"

static void print_quit_message(const int end_status);

int
main(int argc, char ** argv)
{
    process_options(argc, argv);

    struct tge_parameters parameters;
    parameters.setup_function = worms_game_setup;
    parameters.teardown_function = worms_game_teardown;
    parameters.draw_function = worms_draw_screen;
    parameters.input_function = worms_process_input;
    parameters.timer_interval = game_speed / 100.0;

    const int end_status = tge_begin_game(&parameters);
    print_quit_message(end_status);

    return EXIT_SUCCESS;
}

static void
print_quit_message(const int end_status)
{
    switch ( end_status ) {
        case WORMS_EXIT_NORMAL:
            printf("Game over! You quit the game.\n");
            break;

        case WORMS_EXIT_HITWALL:
            printf("Game over! You hit the wall!\n");
            break;

        case WORMS_EXIT_HITSELF:
            printf("Game over! You hit yourself!\n");
            break;

        default:
            printf("Game over! Unknown exit status.\n");
            break;
    }

    printf("You played for %s.\n", worms_game_time_string(true));
    const int score = worms_get_food_eaten();
    printf("You ate %d %s of food.\n", score,
           (score == 1) ? "piece" : "pieces");
}

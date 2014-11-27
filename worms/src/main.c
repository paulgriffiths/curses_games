/*!
 * \file            main.c
 * \brief           main() function for worms game.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdio.h>
#include <stdlib.h>
#include "worms.h"

/*!
 * \brief               Prints a quit message.
 * \details             Prints a quit message.
 * \param end_status    The exit status of the game.
 */
static void print_quit_message(const int end_status);

/*!
 * \brief   main() function.
 * \details main() function.
 * \returns The exit status of the program.
 */
int main(void)
{
    struct tge_parameters parameters;
    parameters.setup_function = worms_game_setup;
    parameters.teardown_function = worms_game_teardown;
    parameters.draw_function = worms_draw_screen;
    parameters.input_function = worms_process_input;
    parameters.timer_interval = .2;

    const int end_status = tge_begin_game(&parameters);
    print_quit_message(end_status);

    return EXIT_SUCCESS;
}

static void print_quit_message(const int end_status)
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

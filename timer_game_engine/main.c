/*!
 * \file            main.c
 * \brief           Main function for timer_game_engine.
 * \details         Main function for timer_game_engine.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <paulgrif/tge.h>


/*!  File scope constant for normal exit status  */
static const int game_normal_exit = 0;

/*!  File scope constant for early exit status  */
static const int game_early_exit = 1;

/*!
 * \brief       Initializes the game.
 * \details     This function is called back by the TGE engine.
 */
void game_init(void);

/*!
 * \brief       Cleans up after the game.
 * \details     This function is called back by the TGE engine.
 */
void game_destroy(int exit_status);

/*!
 * \brief       Draws the game screen.
 * \details     This function is called back by the TGE engine.
 */
void game_draw(void);

/*!
 * \brief       Processes the game input.
 * \details     This function is called back by the TGE engine.
 */
void process_input(const int ch);


/*!
 * \brief       Main function.
 * \returns     Exit status.
 */

int main(void) {

    /*  Populate game parameters structure  */

    struct tge_parameters params;
    params.setup_function = game_init;
    params.teardown_function = game_destroy;
    params.draw_function = game_draw;
    params.input_function = process_input;
    params.timer_interval = 1;

    /*  Enter main game loop  */

    int exit_status = tge_begin_game(&params);

    /*  Print quit message depending on exit status  */

    if ( exit_status == game_normal_exit ) {
        puts("The game exited by itself.");
    }
    else if ( exit_status == game_early_exit ) {
        puts("You exited the game early.");
    }

    return EXIT_SUCCESS;
}


void game_init(void) {
}

void game_destroy(int exit_status) {
    (void)exit_status;  /*  Explicitly ignore parameter  */
}

void game_draw(void) {
    box(stdscr, 0, 0);

    static int count = 0;
    if ( count <= 5 ) {
        move(2 + count, 2);
        if ( count ) {
            printw("Game iteration %d", count);
        }
        else {
            addstr("Game has started! Press 'Q' to exit early.");
        }
        ++count;
    }
    else {
        tge_end_game(game_normal_exit);
    }

    refresh();
}

void process_input(const int ch) {
    if ( ch == 'q' || ch == 'Q' ) {
        tge_end_game(game_early_exit);
    }
}

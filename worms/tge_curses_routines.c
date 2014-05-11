/*!
 * \file            tge_curses_routines.c
 * \brief           Implementation of TGE general curses functions.
 * \details         Implementation of TGE general curses functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  POSIX feature test macro  */
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <curses.h>
#include "tge.h"

/*!
 * \brief       Structure for main game window
 */
struct gw {
    WINDOW * window;    /*!<  Pointer to main curses window         */
    struct winsize ws;  /*!<  Contains dimensions of terminal       */
    int old_cursor;     /*!<  To store the old cursor               */
    bool initialized;   /*!<  true if initialized, false otherwise  */
};

/*!  File scope variable to hold main game window  */
static struct gw game_window = {NULL, {0, 0, 0, 0}, 0, false};

void tge_initialize_screen(void) {
    assert(game_window.initialized == false);

    if ( game_window.initialized == false ) {
        if ( (game_window.window = initscr()) == NULL ) {
            perror("worms: couldn't initialize screen");
            exit(EXIT_FAILURE);
        }

        if ( ioctl(0, TIOCGWINSZ, &game_window.ws) == -1 ) {
            perror("worms: couldn't get terminal size");
            exit(EXIT_FAILURE);
        }

        noecho();
        keypad(game_window.window, true);
        crmode();
        game_window.old_cursor = curs_set(0);
        game_window.initialized = true;
        refresh();
    }
}

void tge_free_screen(void) {
    assert(game_window.initialized == true);

    if ( game_window.initialized == true ) {
        delwin(game_window.window);
        curs_set(game_window.old_cursor);
        endwin();
        refresh();
        game_window.initialized = false;
    }
}
    
WINDOW * tge_main_window(void) {
    assert(game_window.window);
    return game_window.window;
}

int tge_get_character(void) {
    int c = getch();
    return (c == ERR) ? -1 : c;
}

int tge_term_rows(void) {
    return game_window.ws.ws_row;
}

int tge_term_cols(void) {
    return game_window.ws.ws_col;
}


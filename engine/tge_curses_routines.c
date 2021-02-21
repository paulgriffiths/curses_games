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

#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <curses.h>

#include "tge.h"
#include "util.h"

struct gw {
    WINDOW * window;
    struct winsize ws;
    int old_cursor;
    bool initialized;
};

static struct gw game_window = {
    .window = NULL,
    .ws = {0, 0, 0, 0},
    .old_cursor = 0,
    .initialized = false,
};

void
tge_initialize_screen(void) {
    assert(game_window.initialized == false);

    if ( game_window.initialized == false ) {
        if ( (game_window.window = initscr()) == NULL ) {
            x_perror("failed to initialize screen");
        }

        if ( ioctl(0, TIOCGWINSZ, &game_window.ws) == -1 ) {
            x_perror("failed to get terminal size");
        }

        noecho();
        keypad(game_window.window, true);
        crmode();
        game_window.old_cursor = curs_set(0);
        game_window.initialized = true;
        refresh();
    }
}

void
tge_free_screen(void) {
    assert(game_window.initialized == true);

    if ( game_window.initialized == true ) {
        delwin(game_window.window);
        curs_set(game_window.old_cursor);
        endwin();
        refresh();
        game_window.initialized = false;
    }
}
    
WINDOW *
tge_main_window(void) {
    return game_window.window;
}

int
tge_get_character(void) {
    int c = getch();
    return (c == ERR) ? -1 : c;
}

int
tge_term_rows(void) {
    return game_window.ws.ws_row;
}

int
tge_term_cols(void) {
    return game_window.ws.ws_col;
}

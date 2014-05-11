#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <curses.h>
#include "tge.h"

struct gw {
    WINDOW * window;
    struct winsize ws;
    int old_cursor;
    bool initialized;
};

static struct gw game_window = {NULL, {0, 0, 0, 0}, 0, false};

void tge_initialize_screen(void) {
    assert(game_window.initialized == false);

    if ( game_window.initialized == false ) {
        if ( (game_window.window = initscr()) == NULL ) {
            fputs("worms: couldn't initialize screen.", stderr);
            exit(EXIT_FAILURE);
        }

        if ( ioctl(0, TIOCGWINSZ, &game_window.ws) == -1 ) {
            fputs("worms: couldn't get terminal size.", stderr);
            exit(EXIT_FAILURE);
        }

        noecho();
        keypad(game_window.window, true);
        game_window.old_cursor = curs_set(0);
        game_window.initialized = true;
        refresh();
    }
}

WINDOW * tge_main_window(void) {
    assert(game_window.window);
    return game_window.window;
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
    
int tge_get_character(void) {
    int c = getch();
    return (c == ERR) ? -1 : c;
}

int tge_term_width(void) {
    return game_window.ws.ws_col;
}

int tge_term_height(void) {
    return game_window.ws.ws_row;
}

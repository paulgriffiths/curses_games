#ifndef PG_TIMER_GAME_ENGINE_CURSES_ROUTINES_H
#define PG_TIMER_GAME_ENGINE_CURSES_ROUTINES_H

#include <curses.h>

void tge_initialize_screen(void);
WINDOW * tge_main_window(void);
void tge_free_screen(void);
int tge_get_character(void);
int tge_term_height(void);
int tge_term_width(void);

#endif      /*  PG_TIMER_GAME_ENGINE_CURSES_ROUTINES_H  */

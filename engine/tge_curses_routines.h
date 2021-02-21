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

#ifndef PG_CURSES_GAMES_ENGINE_TGE_CURSES_ROUTINES_H
#define PG_CURSES_GAMES_ENGINE_TGE_CURSES_ROUTINES_H

#include "internal.h"

#include <curses.h>

void tge_initialize_screen(void);
void tge_free_screen(void);
WINDOW * tge_main_window(void);
int tge_get_character(void);
int tge_term_rows(void);
int tge_term_cols(void);

#endif      /*  PG_CURSES_GAMES_ENGINE_TGE_CURSES_ROUTINES_H  */

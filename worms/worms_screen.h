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

#ifndef PG_CURSES_GAMES_WORMS_WORMS_SCREEN_H
#define PG_CURSES_GAMES_WORMS_WORMS_SCREEN_H

#include "internal.h"

#include <stdbool.h>

/* Enumeration constants for game cell characters */
enum worms_cell_character {
    WORM_BODY_CHARACTER,
    WORM_EMPTY_CHARACTER,
    WORM_FOOD_CHARACTER
};

void worms_game_area_init(void);
void worms_game_area_destroy(void);
void worms_draw_arena_border(void);
void worms_draw_sidebar(void);
void worms_refresh_game_area(void);
int worms_game_arena_cols(void);
int worms_game_arena_rows(void);
void worms_write_arena_character(const enum worms_cell_character ch,
                                 const int x, const int y);
enum worms_cell_character worms_get_arena_character(const int x, const int y);
bool worms_coords_in_game_arena(const int x, const int y);

#endif      /*  PG_CURSES_GAMES_WORMS_WORMS_SCREEN_H  */


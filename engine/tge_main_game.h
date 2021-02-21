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

#ifndef PG_CURSES_GAMES_ENGINE_MAIN_GAME_H
#define PG_CURSES_GAMES_ENGINE_MAIN_GAME_H

#include "internal.h"

struct tge_parameters {
    void (*setup_function)(void);
    void (*draw_function)(void);
    void (*input_function)(int);
    void (*teardown_function)(int);
    double timer_interval;
};

int tge_begin_game(const struct tge_parameters * parameters);
void tge_end_game(const int status);

#endif      /*  PG_CURSES_GAMES_ENGINE_MAIN_GAME_H  */


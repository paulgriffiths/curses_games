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

#ifndef PG_CURSES_GAMES_WORMS_WORMS_TIME_H
#define PG_CURSES_GAMES_WORMS_WORMS_TIME_H

#include "internal.h"

#include <stdbool.h>

void worms_time_init(void);
long worms_game_time(void);
char * worms_game_time_string(const bool long_format);

#endif      /*  PG_CURSES_GAMES_WORMS_WORMS_TIME_H  */


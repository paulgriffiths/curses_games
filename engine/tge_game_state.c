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

#include <signal.h>

#include "tge.h"

enum game_state {
    TGE_GAME_STATE_NOTSTARTED,
    TGE_GAME_STATE_RUNNING,
    TGE_GAME_STATE_ENDED
};

static volatile sig_atomic_t tge_end_status_var = 0;
static volatile sig_atomic_t game_state = TGE_GAME_STATE_NOTSTARTED;
static volatile sig_atomic_t refresh_flag = true;

void
tge_start_game(void) {
    game_state = TGE_GAME_STATE_RUNNING;
}

bool
tge_game_started(void) {
    return game_state == TGE_GAME_STATE_RUNNING;
}

void
tge_end_game(const int status) {
    tge_end_status_var = status;
    game_state = TGE_GAME_STATE_ENDED;
}

bool
tge_game_ended(void) {
    return game_state == TGE_GAME_STATE_ENDED;
}

int
tge_end_status(void) {
    return tge_end_status_var;
}

void
tge_set_needs_refresh(const bool status) {
    refresh_flag = status;
}

bool
tge_needs_refresh(void) {
    return refresh_flag;
}

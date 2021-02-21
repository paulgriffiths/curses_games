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

#include "worms.h"

void
worms_game_setup(void)
{
    worms_game_area_init();
    worm_init();
    worms_place_new_food();
    worms_time_init();
}

void
worms_game_teardown(const int end_status)
{
    worm_destroy();
    worms_game_area_destroy();
    (void)end_status;   /*  Explicitly discard argument  */
}

void
worms_draw_screen(void)
{
    worms_draw_arena_border();
    worms_draw_sidebar();
    worms_draw_food();

    if ( worm_move_and_draw() ) {
        /*  Worm ate food on its move, so draw new food  */
        worms_place_new_food();
        worms_draw_food();
    }

    worms_refresh_game_area();
}

void
worms_process_input(const int ch)
{
    switch ( ch ) {
        case 'h':
        case 'H':
        case KEY_LEFT:
            worm_set_direction(WORM_DIR_LEFT);
            break;

        case 'j':
        case 'J':
        case KEY_DOWN:
            worm_set_direction(WORM_DIR_DOWN);
            break;

        case 'k':
        case 'K':
        case KEY_UP:
            worm_set_direction(WORM_DIR_UP);
            break;

        case 'l':
        case 'L':
        case KEY_RIGHT:
            worm_set_direction(WORM_DIR_RIGHT);
            break;

        case 'q':
        case 'Q':
            tge_end_game(WORMS_EXIT_NORMAL);
            break;
    }
}

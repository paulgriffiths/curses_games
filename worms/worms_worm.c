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

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "worms.h"
#include "util.h"

/* Structure to hold an individual cell of the worm's body */
struct cell {
    int x;
    int y;
    struct cell * front;
    struct cell * back;
};

/* Structure to hold the worm */
struct worm {
    struct cell * head;
    struct cell * tail;
    enum worm_direction last_direction;
    enum worm_direction next_direction;
};

/* File scope variable to contain the worm */
static struct worm worm = {NULL, NULL, WORM_DIR_RIGHT, WORM_DIR_RIGHT};

/* File scope constant containing initial length of worm */
static const size_t WORM_START_LENGTH = 8;

/* Static function declarations */
static void worm_clear(void);
static bool worm_move(void);
static void worm_draw(void);
static bool worm_cell_here(const int x, const int y);
static void worm_add_cell_head(const int x, const int y);
static void worm_delete_cell_head(void);
static void worm_delete_cell_tail(void);

void
worm_init(void)
{
    for ( size_t x = 2; x <= WORM_START_LENGTH + 2; ++x ) {
        worm_add_cell_head(x, 10);
    }
}

void
worm_destroy(void)
{
    while ( worm.head ) {
        worm_delete_cell_head();
    }
}

void
worm_set_direction(enum worm_direction direction)
{
    if ( abs(worm.last_direction - direction) != 2 ) {
        worm.next_direction = direction;
    }
}

bool
worm_move_and_draw(void)
{
    worm_clear();
    const bool move = worm_move();
    worm_draw();
    return move;
}

static
void worm_clear(void)
{
    const struct cell * cell = worm.tail;
    while ( cell ) {
        worms_write_arena_character(WORM_EMPTY_CHARACTER, cell->x, cell->y);
        cell = cell->front;
    }
}

static
bool worm_move(void)
{
    int x, y;
    bool food_eaten = false;

    /*  Calculate coordinates of new head based on next direction  */
    switch ( worm.next_direction ) {
        case WORM_DIR_UP:
            x = worm.head->x;
            y = worm.head->y - 1;
            break;

        case WORM_DIR_RIGHT:
            x = worm.head->x + 1;
            y = worm.head->y;
            break;

        case WORM_DIR_DOWN:
            x = worm.head->x;
            y = worm.head->y + 1;
            break;

        case WORM_DIR_LEFT:
            x = worm.head->x - 1;
            y = worm.head->y;
            break;

        default:
            assert(false);
            break;
    }

    /*  Perform collision detection  */
    if ( worms_coords_in_game_arena(x, y) ) {

        /*  The worm didn't hit the arena wall if we're here  */
        if ( worm_cell_here(x, y) ) {
            /*  The worm hit its own body, so end game  */
            tge_end_game(WORMS_EXIT_HITSELF);
        }
        else {
            /*  The worm didn't hit the arena wall, or
             *  its own body, so the game will continue
             *  and the worm will successfully move.     */
            worm.last_direction = worm.next_direction;

            if ( worms_food_here(x, y) ) {
                /*  The worm ate some food, so set return status
                 *  and do NOT delete the current tail cell,
                 *  since the worm should grow when it eats food.  */
                food_eaten = true;
            }
            else {
                /*  The worm did not eat some food, so leave return
                 *  status as is, and delete the current tail cell,
                 *  leaving the worm the same length as before.      */
                worm_delete_cell_tail();
            }

            /*  Add a new head cell at the moved-to coordinates  */
            worm_add_cell_head(x, y);
        }
    }
    else {
        /*  The worm hit the arena wall, so end game  */
        tge_end_game(WORMS_EXIT_HITWALL);
    }

    return food_eaten;
}

static void
worm_draw(void)
{
    const struct cell * cell = worm.tail;
    while ( cell ) {
        worms_write_arena_character(WORM_BODY_CHARACTER, cell->x, cell->y);
        cell = cell->front;
    }
}

static bool
worm_cell_here(const int x, const int y)
{
    const struct cell * cell = worm.tail;
    while ( cell ) {
        if ( cell->x == x && cell->y == y ) {
            return true;
        }
        cell = cell->front;
    }
    return false;
}

static void
worm_add_cell_head(const int x, const int y)
{
    struct cell * new_cell = x_malloc(sizeof *new_cell);
    new_cell->x = x;
    new_cell->y = y;
    new_cell->front = NULL;

    if ( worm.head == NULL ) {
        new_cell->back = NULL;
        worm.head = new_cell;
        worm.tail = new_cell;
    }
    else {
        new_cell->back = worm.head;
        worm.head->front = new_cell;
        worm.head = new_cell;
    }
}

static void
worm_delete_cell_head(void)
{
    if ( worm.head ) {
        struct cell * new_head = worm.head->back;

        if ( new_head ) {
            /*  Only update the new head if there will be one  */
            new_head->front = NULL;
        }
        else {
            /*  Worm will be empty, so set tail to NULL also  */
            worm.tail = NULL;
        }

        free(worm.head);
        worm.head = new_head;
    }
}

static void
worm_delete_cell_tail(void)
{
    if ( worm.tail ) {
        struct cell * new_tail = worm.tail->front;

        if ( new_tail ) {
            /*  Only update the new tail if there will be one  */
            new_tail->back = NULL;
        }
        else {
            /*  Worm will be empty, so set head to NULL also  */
            worm.head = NULL;
        }

        free(worm.tail);
        worm.tail = new_tail;
    }
}

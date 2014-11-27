/*!
 * \file            worms_food.c
 * \brief           Implementation of worm food functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <stdlib.h>
#include "worms.h"

/*!  File scope variable for x coordinate of current food piece  */
static int food_x = 0;

/*!  File scope variable for y coordinate of current food piece  */
static int food_y = 0;

/*!  File scope variable for total food eaten since start of game  */
static int food_eaten = -1;

void worms_place_new_food(void)
{
    bool keep_searching = true;
    const int arena_cols = worms_game_arena_cols();
    const int arena_rows = worms_game_arena_rows();

    while ( keep_searching ) {

        /*
         *  NOTE: This algorithm has the potential to run for
         *  a very long time if there are very few empty
         *  characters left in the game arena. There will come
         *  a number of iterations at which it would be more
         *  efficient to switch to a more time-consuming but
         *  more definitely-bounded algorithm, e.g. calculating
         *  the number of empty characters in the arena, selecting
         *  a random number within that range, and then stepping
         *  through all the arena characters until the nth empty
         *  character is found.
         */

        /*  Calculate random position inside arena borders  */

        food_x = 1 + (rand() % (arena_cols - 2));
        food_y = 1 + (rand() % (arena_rows - 2));

        /*  Exit loop if selected position is empty  */

        if ( worms_get_arena_character(food_x, food_y) !=
                WORM_BODY_CHARACTER ) {
            keep_searching = false;
        }
    }

    ++food_eaten;
}

void worms_draw_food(void)
{
    worms_write_arena_character(WORM_FOOD_CHARACTER, food_x, food_y);
}

bool worms_food_here(const int x, const int y)
{
    return (x == food_x && y == food_y) ? true : false;
}

int worms_get_food_eaten(void)
{
    return food_eaten;
}


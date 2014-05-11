/*!
 * \file            worms_food.c
 * \brief           Interface to worm food functions.
 * \details         Interface to worm food functions for curses worms game.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_WORMS_GAME_WORM_FOOD_H
#define PG_WORMS_GAME_WORM_FOOD_H

/*!
 * \brief       Places a new piece of food at a random location.
 * \details     Places a new piece of food at a random location.
 */
void worms_place_new_food(void);

/*!
 * \brief       Draws the current piece of food.
 * \details     Draws the current piece of food.
 */
void worms_draw_food(void);

/*!
 * \brief       Tests if a piece of food is at the specified coordinates.
 * \details     Tests if a piece of food is at the specified coordinates.
 * \param x     The specified x coordinate.
 * \param y     The specified y coordinate.
 * \returns     `true` if a piece of food is at the specified coordinates,
 * `false` otherwise.
 */
bool worms_food_here(const int x, const int y);

/*
 * \brief       Returns the total number of pieces of food eaten.
 * \details     Returns the total number of pieces of food eaten since
 * the start of the game.
 * \returns     The total number of pieces of food eaten since the start
 * of the game.
 */
int worms_get_food_eaten(void);

#endif      /*  PG_WORMS_GAME_WORM_FOOD_H  */


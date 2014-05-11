/*!
 * \file            worms_worm.h
 * \brief           Interface to worms game worm functions.
 * \details         Interface to worms game worm functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_WORMS_GAME_WORMS_WORM_H
#define PG_WORMS_GAME_WORMS_WORM_H

#include <stdbool.h>

/*!
 * \brief   Enumeration constants for worm movement direction.
 * \details Enumeration constants for worm movement direction. The order
 * in which these are defined is meaningful to the implementation, namely
 * that pairs of opposing directions (i.e. up versus down, left versus right)
 * have values with an absolute difference of 2.
 */
enum worm_direction {
    WORM_DIR_UP,        /*!<  Up direction      */
    WORM_DIR_RIGHT,     /*!<  Right direction   */
    WORM_DIR_DOWN,      /*!<  Down direction    */
    WORM_DIR_LEFT       /*!<  Left direction    */
};

/*!
 * \brief   Initializes the worm.
 * \details Initializes and allocates memory for the worm.
 */
void worm_init(void);

/*!
 * \brief   Destroys the worm.
 * \details Destroys and deallocates memory for the worm.
 */
void worm_destroy(void);

/*!
 * \brief   Attempts to change the next direction of the worm.
 * \details Attempts to change the next direction of the worm. The worm
 * will not actually change direction until the game next updates, and
 * a second call to this function in the interim will nullify the effect
 * of any previous calls, so it is safe to call this function an arbitrary
 * number of times in between game updates. This function will ignore
 * any attempt to change the direction in a way which is not allowed,
 * particularly that the worm is not allowed to turn 180 degrees as this
 * would cause it to hit its own body, so it is safe to call this function
 * with any direction, and to trust it to ignore any direction changes
 * which are not allowed.
 * \param direction The desired direction of the worm on the next update.
 */
void worm_set_direction(enum worm_direction direction);

/*!
 * \brief       Moves and draws the worm.
 * \details     Moves and draws the worm.
 * \returns     `true` if the movement that was performed caused the worm
 * to eat a piece of food, `false` in all other situations.
 */
bool worm_move_and_draw(void);

#endif      /*  PG_WORMS_GAME_WORMS_WORM_H  */


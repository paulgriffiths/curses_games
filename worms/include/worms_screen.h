/*!
 * \file            worms_screen.h
 * \brief           Interface to worms game screen functions.
 * \details         Interface to worms game screen functions. The game
 * screen consists of two parts: the "arena", where the worm moves, and
 * the "sidebar", containing the game title and game statistics. "Game area"
 * can also refer to the entire game screen.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_WORMS_GAME_WORMS_SCREEN_H
#define PG_WORMS_GAME_WORMS_SCREEN_H

#include <stdbool.h>

/*!  Enumeration constants for game cell characters  */
enum worms_cell_character {
    WORM_BODY_CHARACTER,    /*!<  Character for worm body       */
    WORM_EMPTY_CHARACTER,   /*!<  Character for empty cell      */
    WORM_FOOD_CHARACTER     /*!<  Character for piece of food   */
};

/*!
 * \brief   Initializes the game area, including the sidebar.
 * \details Initializes the game area, including the sidebar.
 */
void worms_game_area_init(void);

/*!
 * \brief   Destroys the game area, including the sidebar.
 * \details Destroys the game area, including the sidebar.
 */
void worms_game_area_destroy(void);

/*!
 * \brief   Draws a border around the game arena.
 * \details Draws a border around the game arena.
 */
void worms_draw_arena_border(void);

/*!
 * \brief   Draws the sidebar.
 * \details Draws the sidebar.
 */
void worms_draw_sidebar(void);

/*!
 * \brief   Refreshes the main arena and the sidebar.
 * \details Refreshes the main arena and the sidebar.
 */
void worms_refresh_game_area(void);

/*!
 * \brief   Returns the number of columns in the game arena.
 * \details Returns the number of columns in the game arena. The
 * number of columns *includes* the arena border, which is one
 * character wide on all sides.
 * \returns The number of columns in the game arena.
 */
int worms_game_arena_cols(void);

/*!
 * \brief   Returns the number of rows in the game arena.
 * \details Returns the number of rows in the game arena. The
 * number of rows *includes* the arena border, which is one
 * character wide on all sides.
 * \returns The number of rows in the game arena.
 */
int worms_game_arena_rows(void);

/*!
 * \brief       Writes a character to the game arena.
 * \details     Writes a character to the game arena.
 * \param ch    The character to write.
 * \param x     The x coordinate at which to write the character.
 * \param y     The y coordinate at which to write the character.
 */
void worms_write_arena_character(const enum worms_cell_character ch,
                                 const int x, const int y);

/*!
 * \brief       Returns the character at the specified arena coordinates.
 * \details     Returns the character at the specified arena coordinates.
 * \param x     The specified x coordinate.
 * \param y     The specified y coordinate.
 * \returns     The character at the specified coordinates in the arena.
 */
enum worms_cell_character worms_get_arena_character(const int x, const int y);

/*!
 * \brief       Tests if the specified coordinates are within the arena.
 * \details     Tests if the specified coordinates are within the arena.
 * The coordinates are *not* considered to be within the arena if they
 * are within the arena's border, so this test is suitable for determining
 * whether the worm has hit the border at the edge of the arena.
 * \param x     The specified x coordinate.
 * \param y     The specified y coordinate.
 * \returns     `true` if the specified coordinates are within the arena,
 * excluding the arena border, and `false` otherwise.
 */
bool worms_coords_in_game_arena(const int x, const int y);

#endif      /*  PG_WORMS_GAME_WORMS_SCREEN_H  */


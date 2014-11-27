/*!
 * \file            worms_game.h
 * \brief           Interface to TGE game engine callback functions.
 * \details         Interface to TGE game engine callback functions, along
 * with general game data structures and constants.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_WORMS_GAME_WORMS_GAME_H
#define PG_WORMS_GAME_WORMS_GAME_H


/*!
 * \brief   Enumeration constants for game exit status
 * \details Enumeration constants for game exit status.
 */
enum worms_exit_status {
    WORMS_EXIT_NORMAL,      /*!< Player chose to quit           */
    WORMS_EXIT_HITWALL,     /*!< Worm ran into the arena wall   */
    WORMS_EXIT_HITSELF      /*!< Worm ran into its own body     */
};

/*!
 * \brief       Initializes the game.
 * \details     Initializes the game area, worm, worm food, and game time.
 */
void worms_game_setup(void);

/*!
 * \brief               Cleans up after the game ends.
 * \details             Destroys the worm and the game area.
 * \param end_status    Status code for end-of-game reason.
 */
void worms_game_teardown(const int end_status);

/*!
 * \brief       Draws the game screen at each timer interval.
 * \details     Draws the game screen at each timer interval.
 */
void worms_draw_screen(void);

/*!
 * \brief       Processes keyboard input.
 * \details     Processes keyboard input to move the worm or quit the game.
 * \param ch    Character code representing the key pressed.
 */
void worms_process_input(const int ch);

#endif      /*  PG_WORMS_GAME_WORMS_GAME_H  */

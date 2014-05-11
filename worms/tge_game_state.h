/*!
 * \file            tge_game_state.h
 * \brief           Interface to TGE game state functions.
 * \details         Interface to TGE game state functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_TIMER_GAME_ENGINE_TGE_GAME_STATE_H
#define PG_TIMER_GAME_ENGINE_TGE_GAME_STATE_H

#include <stdbool.h>

/*!
 * \brief       Starts the timer game.
 * \details     Starts the timer game.
 */
void tge_start_game(void);

/*!
 * \brief       Tests if the timer game has started.
 * \details     Tests if the timer game has started.
 * \returns     `true` if the timer game has started, `false` otherwise.
 */
bool tge_game_started(void);

/*!
 * \brief           Ends the timer game.
 * \details         Ends the timer game.
 * \param status    The exit status of the game.
 */
void tge_end_game(const int status);

/*!
 * \brief       Tests if the timer game has ended.
 * \details     Tests if the timer game has ended.
 * \returns     `true` if the timer game has ended, `false` otherwise.
 */
bool tge_game_ended(void);

/*!
 * \brief       Returns the timer game exit status.
 * \details     Returns the timer game exit status. The meaning of this
 * value is defined by the application using the TGE library.
 * \returns     The timer game exit status.
 */
int tge_end_status(void);

/*!
 * \brief           Notifies the library that the game needs updating.
 * \details         Notifies the library that the game needs updating. This
 * is typically called by the `SIGALRM` signal handler in response to the
 * game timer, but could be called by the application.
 * \param status    `true` to turn on the "needs updating" flag, `false`
 * to turn it off.
 */
void tge_set_needs_refresh(const bool status);

/*!
 * \brief       Checks if the game needs updating.
 * \details     Checks if the game needs updating. This function returns
 * the state set by `tge_set_needs_refresh()`.
 * \returns     `true` is the game needs updating, `false` otherwise.
 */
bool tge_needs_refresh(void);

#endif      /*  PG_TIMER_GAME_ENGINE_TGE_GAME_STATE_H  */

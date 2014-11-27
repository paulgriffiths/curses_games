/*!
 * \file            tge_signals.h
 * \brief           Interface to TGE signals functions.
 * \details         Interface to TGE signals functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_TIMER_GAME_ENGINE_TGE_SIGNALS_H
#define PG_TIMER_GAME_ENGINE_TGE_SIGNALS_H

/*!
 * \brief       Registers the signal handlers.
 * \details     Registers the signal handlers.
 */
void tge_set_signal_handlers(void);

/*!
 * \brief           Starts the game timer.
 * \details         Starts the game timer.
 * \param start     The time until the first alarm, in seconds.
 * \param interval  The time interval between subsequent alarms, in seconds.
 */
void tge_timer_start(const double start, const double interval);

/*!
 * \brief   Stops the game timer.
 * \details Stops the game timer.
 */
void tge_timer_stop(void);

#endif      /*  PG_TIMER_GAME_ENGINE_TGE_SIGNALS_H  */


/*!
 * \file            worms_time.h
 * \brief           Interface to worms game duration timer functions.
 * \details         Interface to worms game duration timer functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_WORMS_GAME_WORMS_TIME_H
#define PG_WORMS_GAME_WORMS_TIME_H

/*!
 * \brief       Initializes the game duration timer.
 * \details     Initializes the game duration timer.
 */
void worms_time_init(void);

/*!
 * \brief       Returns the number of seconds since the game started.
 * \details     Returns the number of seconds since the game started.
 * \returns     The number of seconds since the game started.
 */
long worms_game_time(void);

/*!
 * \brief       Returns a string representation of total game time.
 * \details     Returns a string representation of total game time.
 * \param long_format   If this parameter is `true`, the string
 * representation is of the form "[H] hours, [M] minutes, and [S]
 * seconds". If `false`, the string representation is of the form
 * "HH:MM:SS".
 * \returns     A string representation of the total game time. The
 * returned pointer points to statically allocated storage, and is
 * overwritten each time this function is called.
 */
char * worms_game_time_string(const bool long_format);

#endif      /*  PG_WORMS_GAME_WORMS_TIME_H  */


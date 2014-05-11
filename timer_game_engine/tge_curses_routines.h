/*!
 * \file            tge_curses_routines.h
 * \brief           Interface to TGE general curses functions.
 * \details         Interface to TGE general curses functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_TIMER_GAME_ENGINE_TGE_CURSES_ROUTINES_H
#define PG_TIMER_GAME_ENGINE_TGE_CURSES_ROUTINES_H

#include <curses.h>

/*!
 * \brief       Initializes the game screen.
 * \details     Initializes the game screen.
 */
void tge_initialize_screen(void);

/*!
 * \brief       Frees and destroys the game screen.
 * \details     Frees and destroys the game screen.
 */
void tge_free_screen(void);

/*!
 * \brief       Returns a pointer to the main curses window.
 * \details     Returns a pointer to the main curses window.
 * \returns     A pointer to the main curses window.
 */
WINDOW * tge_main_window(void);

/*!
 * \brief       Gets a character input by the player.
 * \details     Gets a character input by the player. This function will
 * not block if no input is ready.
 * \returns     The character input by the player, or -1 if no character
 * was ready.
 */
int tge_get_character(void);

/*!
 * \brief       Returns the number of rows in the terminal.
 * \details     Returns the number of rows in the terminal.
 * \returns     The number of rows in the terminal.
 */
int tge_term_rows(void);

/*!
 * \brief       Returns the number of columns in the terminal.
 * \details     Returns the number of columns in the terminal.
 * \returns     The number of columns in the terminal.
 */
int tge_term_cols(void);

#endif      /*  PG_TIMER_GAME_ENGINE_TGE_CURSES_ROUTINES_H  */

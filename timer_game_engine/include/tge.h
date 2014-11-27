/*!
 * \file            tge.h
 * \brief           Aggregated header for curses timer game engine functions.
 * \details         Aggregated header for curses timer game engine functions.
 *
 * A "timer game" is here defined as a game with two properties:
 *  - the game and display regularly updates at a specified time interval; and
 *  - the game can receive keyboard input at any time.
 *
 * The rationale for providing this framework is twofold. Firstly, to
 * encapsulate some of the overhead of setting up the game, including
 * initializing curses, setting up signal handlers, and controlling the
 * overall flow of the game. Secondly, to solve the programming problem
 * of asynchronously updating the game while waiting on user input.
 *
 * An initial naive implementation may be to implement the game timer
 * using `SIGALRM`, and update the screen in the signal handler, while
 * simply blocking on user input in the main thread. However, the curses
 * functions are not re-entrant, and neither are many standard library
 * functions, so this approach is not reliable. Similar objections would
 * apply to a threads-based approach where one thread blocks on input,
 * and a second thread updates the screen.
 *
 * A second naive implementation would be to simply poll for input without
 * blocking, which would be an unnecessary waste of processor time.
 *
 * The solution here is to wait for input with `select()` to avoid
 * blocking on any input. The game timer is implemented with `SIGALRM`, and
 * the signal handler simply sets an "updated needed" variable and has
 * the automatic side-effect of interrupting `select()` (note: portable
 * curses programs cannot make any assumptions about whether handled signals
 * will interrupt any curses input functions, so `select()` is necessary).
 *
 * The library implements a game loop which begins by checking if a screen
 * update is necessary. If it is, the screen is updated, and the loop
 * re-entered. If it is not, the loop waits on `select()`. If no input is
 * entered, `select()` will interrupt on handling `SIGALRM` and continue to the
 * next iteration of the loop, and the screen will be updated again. If
 * input is entered, `select()` will return and the input can be obtained
 * without blocking. 
 *
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_TIMER_GAME_ENGINE_H
#define PG_TIMER_GAME_ENGINE_H

#include "tge_main_game.h"
#include "tge_curses_routines.h"
#include "tge_game_state.h"
#include "tge_signals.h"

#endif      /*  PG_TIMER_GAME_ENGINE_H  */


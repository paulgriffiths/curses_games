/*!
 * \file            tge_main_game.h
 * \brief           Interface to curses timer game engine main game functions.
 * \details         Interface to curses timer game engine main game functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_TIMER_GAME_ENGINE_MAIN_GAME_H
#define PG_TIMER_GAME_ENGINE_MAIN_GAME_H

/*!
 * \brief       Structre for containing game parameters.
 */
struct tge_parameters {
    void (*setup_function)(void);   /*!<  Setup/initialization function */
    void (*draw_function)(void);    /*!<  Draw function                 */
    void (*input_function)(int);    /*!<  Input handling function       */
    void (*teardown_function)(int); /*!<  Cleanup function              */
    double timer_interval;          /*!<  Timer interval, in seconds    */
};

/*!
 * \brief               Begins the timer game.
 * \details             Begins the timer game.
 * \param parameters    A pointer to a `struct tge_parameters` object
 * containing the desired game parameters.
 * \returns             The exit status of the game.
 */
int tge_begin_game(const struct tge_parameters * parameters);

/*!
 * \brief           Ends the timer game.
 * \details         Ends the timer game.
 * \param status    The exit status for the game.
 */
void tge_end_game(const int status);

#endif      /*  PG_TIMER_GAME_ENGINE_MAIN_GAME_H  */


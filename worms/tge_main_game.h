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

struct tge_parameters {
    void (*setup_function)(void);
    void (*draw_function)(void);
    void (*input_function)(int);
    void (*teardown_function)(int);
    double timer_interval;
};

int tge_begin_game(struct tge_parameters * parameters);
void tge_end_game(const int status);

#endif      /*  PG_TIMER_GAME_ENGINE_MAIN_GAME_H  */


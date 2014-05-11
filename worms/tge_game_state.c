/*!
 * \file            tge_game_state.c
 * \brief           Implementation of TGE game state functions.
 * \details         Implementation of TGE game state functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include "tge.h"

/*!
 * \brief   Enumeration constants for game state.
 */
enum game_state {
    TGE_GAME_STATE_NOTSTARTED,  /*!<  Game has not started      */
    TGE_GAME_STATE_RUNNING,     /*!<  Game has started          */
    TGE_GAME_STATE_ENDED        /*!<  Game has ended            */
};

/*!  File scope variable for current exit status  */
static int tge_end_status_var = 0;

/*!  File scope variable for current game state  */
static enum game_state game_state = TGE_GAME_STATE_NOTSTARTED;

/*!  File scope variable for "needs updating" flag  */
static bool refresh_flag = true;

void tge_start_game(void) {
    game_state = TGE_GAME_STATE_RUNNING;
}

bool tge_game_started(void) {
    return game_state == TGE_GAME_STATE_RUNNING;
}

void tge_end_game(const int status) {
    tge_end_status_var = status;
    game_state = TGE_GAME_STATE_ENDED;
}

bool tge_game_ended(void) {
    return game_state == TGE_GAME_STATE_ENDED;
}

int tge_end_status(void) {
    return tge_end_status_var;
}

void tge_set_needs_refresh(const bool status) {
    refresh_flag = status;
}

bool tge_needs_refresh(void) {
    return refresh_flag;
}


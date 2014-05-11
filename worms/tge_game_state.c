#include "tge.h"

enum game_state {
    TGE_GAME_STATE_NOTSTARTED,
    TGE_GAME_STATE_RUNNING,
    TGE_GAME_STATE_ENDED
};

static int tge_end_status_var = 0;

static enum game_state game_state = TGE_GAME_STATE_NOTSTARTED;
static bool refresh_flag = 1;

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

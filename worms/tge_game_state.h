#ifndef PG_TIMER_GAME_ENGINE_GAME_STATE_H
#define PG_TIMER_GAME_ENGINE_GAME_STATE_H

#include <stdbool.h>

void tge_start_game(void);
bool tge_game_started(void);
void tge_end_game(const int status);
bool tge_game_ended(void);
int tge_end_status(void);
void tge_set_needs_refresh(const bool status);
bool tge_needs_refresh(void);

#endif      /*  PG_TIMER_GAME_ENGINE_GAME_STATE_H  */

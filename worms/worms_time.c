/*  CURSES GAMES, a selection of Unix terminal games.
 *  Copyright (C) 2021 Paul Griffiths.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "worms.h"
#include "util.h"

/* File scope variable to hold the time at the start of the game */
static time_t start_time;

void
worms_time_init(void)
{
    start_time = time(NULL);
    if ( start_time == -1 ) {
        x_perror("failed to get time");
    }
}

long
worms_game_time(void)
{
    const time_t current_time = time(NULL);
    if ( current_time == -1 ) {
        x_perror("failed to get time");
    }
    return (long)difftime(current_time, start_time);
}

char *
worms_game_time_string(const bool long_format)
{
    static char time_string[40] = {0};

    const long game_time = worms_game_time();
    const int seconds = game_time % 60;
    const int minutes = (game_time / 60) % 60;
    const int hours = (game_time / 3600) % 24;

    if ( long_format ) {
        snprintf(time_string, sizeof(time_string) - 2,
                 "%d %s, %d %s and %d %s",
                 hours, (hours == 1) ? "hour" : "hours",
                 minutes, (minutes == 1) ? "minute" : "minutes",
                 seconds, (seconds == 1) ? "second" : "seconds");
    }
    else {
        sprintf(time_string, "%02d:%02d:%02d", hours, minutes, seconds);
    }

    return time_string;
}

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
#include <signal.h>
#include <sys/time.h>

#include "tge.h"
#include "util.h"

/* Static function declarations */
static long tge_get_whole_seconds(const double seconds);
static long tge_get_fractional_microseconds(const double seconds);
static void tge_handler(int signum);

void
tge_set_signal_handlers(void) {

    /*  Fill in sigaction struct  */
    struct sigaction sa = {
        .sa_handler = tge_handler,
        .sa_flags = 0,
    };
    sigemptyset(&sa.sa_mask);

    /*  Set signal handlers for SIGTERM, SIGINT and SIGLARM  */
    if ( sigaction(SIGTERM, &sa, NULL) == -1 ) {
        x_perror("failed to set SIGTERM handler");
    }

    if ( sigaction(SIGINT, &sa, NULL) == -1 ) {
        x_perror("failed to set SIGINT handler");
    }

    if ( sigaction(SIGALRM, &sa, NULL) == -1 ) {
        x_perror("failed to set SIGALRM handler");
    }

    /*  Ignore SIGTSTP  */
    sa.sa_handler = SIG_IGN;
    if ( sigaction(SIGTSTP, &sa, NULL) == -1 ) {
        x_perror("failed to ignore SIGTSTP");
    }
}

void
tge_timer_start(const double start, const double interval) {
    struct itimerval itv = {
        .it_interval.tv_sec = tge_get_whole_seconds(interval),
        .it_interval.tv_usec = tge_get_fractional_microseconds(interval),
        .it_value.tv_sec = tge_get_whole_seconds(start),
        .it_value.tv_usec = tge_get_fractional_microseconds(start),
    };

    if ( setitimer(ITIMER_REAL, &itv, NULL) != 0 ) {
        x_perror("failed to set itimer");
    }
}

void
tge_timer_stop(void) {
    struct itimerval itv = {
        .it_interval.tv_sec = 0,
        .it_interval.tv_usec = 0,
        .it_value.tv_sec = 0,
        .it_value.tv_usec = 0,
    };

    if ( setitimer(ITIMER_REAL, &itv, NULL) == -1 ) {
        x_perror("failed to set itimer");
    }
}

static long
tge_get_whole_seconds(const double seconds) {
    return ((long) seconds);
}

static long
tge_get_fractional_microseconds(const double seconds) {
    const double whole_secs = (double) tge_get_whole_seconds(seconds);
    const double fractional_part = seconds - whole_secs;

    return (long) (fractional_part * 1000000);
}

static void
tge_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            tge_set_needs_refresh(true);
            break;

        case SIGTERM:
        case SIGINT:
            tge_end_game(0);
            break;

        default:
            break;
    }
}

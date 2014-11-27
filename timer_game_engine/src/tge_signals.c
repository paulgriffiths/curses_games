/*!
 * \file            tge_signals.c
 * \brief           Implementation of TGE signals functions.
 * \details         Implementation of TGE signals functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

/*!  POSIX feature test macro  */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include "tge.h"

/*!
 * \brief           Returns the whole seconds part of a seconds value.
 * \details         Returns the whole seconds part of a seconds value.
 * \param seconds   The seconds value.
 * \returns         The whole seconds part of the seconds value.
 */
static long tge_get_whole_seconds(const double seconds);

/*!
 * \brief           Returns the fractional microseconds part of a seconds value.
 * \details         Returns the whole microseconds part of a seconds value.
 * \param seconds   The seconds representation.
 * \returns         The fractional microseconds part of the seconds value.
 */
static long tge_get_fractional_microseconds(const double seconds);

/*!
 * \brief           Generic signal handler.
 * \details         Generic signal handler.
 * \param signum    The signal number.
 */
static void tge_handler(int signum);

void tge_set_signal_handlers(void) {
    struct sigaction sa;

    /*  Fill in sigaction struct  */

    sa.sa_handler = tge_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    /*  Set signal handlers for SIGTERM, SIGINT and SIGLARM  */

    if ( sigaction(SIGTERM, &sa, NULL) == -1 ) {
        perror("tge: couldn't set SIGTERM handler");
        exit(EXIT_FAILURE);
    }
    if ( sigaction(SIGINT, &sa, NULL) == -1 ) {
        perror("tge: couldn't set SIGINT handler");
        exit(EXIT_FAILURE);
    }
    if ( sigaction(SIGALRM, &sa, NULL) == -1 ) {
        perror("tge: couldn't set SIGALRM handler");
        exit(EXIT_FAILURE);
    }

    /*  Ignore SIGTSTP  */

    sa.sa_handler = SIG_IGN;
    if ( sigaction(SIGTSTP, &sa, NULL) == -1 ) {
        perror("tge: couldn't ignore SIGTSTP");
        exit(EXIT_FAILURE);
    }
}

void tge_timer_start(const double start, const double interval) {
    struct itimerval itv;
    itv.it_interval.tv_sec = tge_get_whole_seconds(interval);
    itv.it_interval.tv_usec = tge_get_fractional_microseconds(interval);
    itv.it_value.tv_sec = tge_get_whole_seconds(start);
    itv.it_value.tv_usec = tge_get_fractional_microseconds(start);

    if ( setitimer(ITIMER_REAL, &itv, NULL) != 0 ) {
        perror("tge: couldn't set itimer");
        exit(EXIT_FAILURE);
    }
}

void tge_timer_stop(void) {
    struct itimerval itv;
    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = 0;
    itv.it_value.tv_sec = 0;
    itv.it_value.tv_usec = 0;

    if ( setitimer(ITIMER_REAL, &itv, NULL) == -1 ) {
        perror("tge: couldn't set itimer");
        exit(EXIT_FAILURE);
    }
}

static long tge_get_whole_seconds(const double seconds) {
    return ((long) seconds);
}

static long tge_get_fractional_microseconds(const double seconds) {
    const double whole_secs = (double) tge_get_whole_seconds(seconds);
    const double fractional_part = seconds - whole_secs;
    return (long) (fractional_part * 1000000);
}

static void tge_handler(int signum) {
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


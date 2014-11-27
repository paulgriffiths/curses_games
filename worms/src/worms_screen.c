/*!
 * \file            worms_screen.c
 * \brief           Implementation of worms game screen functions.
 * \details         The game screen consists of two parts: the "arena",
 * where the worm moves, and the "sidebar", containing the game title
 * and game statistics. "Game area" can also refer to the entire game screen.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#include <assert.h>
#include "worms.h"

/*!
 * \brief   Structure to hold details of game windows.
 */
struct game_window {
    WINDOW * window;    /*!<  Pointer to curses WINDOW structure    */
    int rows;           /*!<  Number of rows in the window          */
    int cols;           /*!<  Number of columns in the window       */
};

/*!  File scope variable for number of columns in sidebar  */
static const int sidebar_cols = 20;

/*!  File scope variable for number of rows in title window  */
static const int title_rows = 7;

/*!  File scope variable for main arena window  */
static struct game_window arena_window;

/*!  File scope variable for title window  */
static struct game_window title_window;

/*!  File scope variable for information window  */
static struct game_window info_window;

/*!
 * \brief   Draws the title window in the sidebar.
 * \details Draws the title window in the sidebar.
 */
static void worms_draw_title_window(void);

/*!
 * \brief   Draws the information window in the sidebar.
 * \details Draws the information window in the sidebar.
 */
static void worms_draw_info_window(void);

void worms_game_area_init(void)
{
    WINDOW * main_window = tge_main_window();
    const int cols = tge_term_cols();
    const int rows = tge_term_rows();

    arena_window.window = subwin(main_window,
                                 rows,
                                 cols - sidebar_cols,
                                 0,
                                 0);
    arena_window.cols = cols - sidebar_cols;
    arena_window.rows = rows;

    title_window.window = subwin(main_window,
                                 title_rows,
                                 sidebar_cols,
                                 0,
                                 cols - sidebar_cols);
    title_window.cols = sidebar_cols;
    title_window.rows = title_rows;

    info_window.window = subwin(main_window,
                                rows - title_rows,
                                sidebar_cols,
                                title_rows,
                                cols - sidebar_cols);
    info_window.cols = sidebar_cols;
    info_window.rows = rows - title_rows;
}

void worms_game_area_destroy(void)
{
    delwin(info_window.window);
    delwin(title_window.window);
    delwin(arena_window.window);
}

void worms_draw_arena_border(void)
{
    box(arena_window.window, 0, 0);
}

void worms_draw_sidebar(void)
{
    worms_draw_title_window();
    worms_draw_info_window();
}

void worms_refresh_game_area(void) 
{
    wrefresh(arena_window.window);
    wrefresh(title_window.window);
    wrefresh(info_window.window);
}

int worms_game_arena_cols(void)
{
    return arena_window.cols;
}

int worms_game_arena_rows(void)
{
    return arena_window.rows;
}

void worms_write_arena_character(const enum worms_cell_character ch,
                                 const int x, const int y)
{
    chtype out_ch;
    switch ( ch ) {
        case WORM_BODY_CHARACTER:
            out_ch = 'O';
            break;

        case WORM_EMPTY_CHARACTER:
            out_ch = ' ';
            break;

        case WORM_FOOD_CHARACTER:
            out_ch = ACS_DIAMOND;
            break;

        default:
            assert(false);
            break;
    }

    mvwaddch(arena_window.window, y, x, out_ch);
}

enum worms_cell_character worms_get_arena_character(const int x, const int y)
{
    wmove(arena_window.window, y, x);
    const chtype cell_ch = winch(arena_window.window) & A_CHARTEXT;

    enum worms_cell_character ret_ch;
    switch ( cell_ch ) {
        case 'O':
            ret_ch = WORM_BODY_CHARACTER;
            break;

        case ' ':
            ret_ch = WORM_EMPTY_CHARACTER;
            break;

        default:
            if ( cell_ch == ACS_DIAMOND ) {
                ret_ch = WORM_FOOD_CHARACTER;
            }
            else {
                assert(false);
            }
            break;
    }
    return ret_ch;
}

bool worms_coords_in_game_arena(const int x, const int y)
{
    if ( x > 0 && (x < arena_window.cols - 1) &&
         y > 0 && (y < arena_window.rows - 1) ) {
        return true;
    }
    else {
        return false;
    }
}

static void worms_draw_title_window(void)
{
    box(title_window.window, 0, 0);

    mvwaddstr(title_window.window, 1, 7, "WORMS!");
    mvwaddstr(title_window.window, 3, 9, "by");
    mvwaddstr(title_window.window, 5, 3, "Paul Griffiths");
}

static void worms_draw_info_window(void)
{
    box(info_window.window, 0, 0);

    mvwprintw(info_window.window, 1, 3,
              "Score : %4d", worms_get_food_eaten());
    mvwprintw(info_window.window, 3, 3,
              "Time: %s", worms_game_time_string(false));
}

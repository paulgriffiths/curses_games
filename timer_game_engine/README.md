timer_game_engine
=================

What is it?
-----------

**timer_game_engine** is a curses-based framework for writing games where:
- the game and display regularly update at a specified time interval; and
- the game can receive keyboard input at any time.

The rationale for providing this framework is twofold. Firstly, to
encapsulate some of the overhead of setting up the game, including
initializing curses, setting up signal handlers, and controlling the
overall flow of the game. Secondly, to solve the programming problem
of asynchronously updating the game while waiting on user input.

An initial naive implementation may be to implement the game timer
using `SIGALRM`, and update the screen in the signal handler, while
simply blocking on user input in the main thread. However, the curses
functions are not re-entrant, and neither are many standard library
functions, so this approach is not reliable. Similar objections would
apply to a threads-based approach where one thread blocks on input,
and a second thread updates the screen.

A second naive implementation would be to simply poll for input without
blocking, which would be an unnecessary waste of processor time.

The solution here is to wait for input with `select()` to avoid
blocking on any input. The game timer is implemented with `SIGALRM`, and
the signal handler simply sets an "updated needed" variable and has
the automatic side-effect of interrupting `select()` (note: portable
curses programs cannot make any assumptions about whether handled signals
will interrupt any curses input functions, so `select()` is necessary).

The library implements a game loop which begins by checking if a screen
update is necessary. If it is, the screen is updated, and the loop
re-entered. If it is not, the loop waits on `select()`. If no input is
entered, `select()` will interrupt on handling `SIGALRM` and continue to the
next iteration of the loop, and the screen will be updated again. If
input is entered, `select()` will return and the input can be obtained
without blocking. 

Who maintains it?
-----------------
**timer_game_engine** is written and maintained by Paul Griffiths.

The latest version
------------------
Details of the latest version can be found on the GitHub project page at
<https://github.com/paulgriffiths/curses_games>.

Documentation
-------------
Up-to-date documentation can be found at
<https://github.com/paulgriffiths/curses_games/wiki>.

Installation
------------
**timer_game_engine** is written in C. Type `make` to build the library,
and `make install` to install it. By default, the library is installed in
the user's home directory in a directory called `lib/c`, and the associated
headers are installed in the user's home directory in a directory called
`include/paulgrif`. Both directories are created if they do not already exist.
To use the library, `#include <paulgrif/tge.h>` in your program and link
with `-lpg_curses_tge`. You may need to modify the makefile or your
`C_INCLUDE_PATH` enviroment variable to include the header directory in your
include search path, or to include the provide the folder to the C compiler
with the `-I` option.

A short sample program using the library is included. Type `make sample` to
build this program, and then `./sample` to run it.

Licensing
---------
Please see the file called LICENSE.

Contacts
--------
* If you have a concrete bug report for **timer_game_engine** please go to
the GitHub issue tracker at
<https://github.com/paulgriffiths/curses_games/issues>.

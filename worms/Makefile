# Worms makefile
# ==============
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Library and executable names
OUT=worms

# Compiler and archiver executable names
CC=cc

# Compiler flags
CFLAGS=-std=c99 -pedantic -Wall -Wextra
C_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=-lncurses 

# Object code files
OBJS=main.o
OBJS+=tge_curses_routines.o tge_main_game.o tge_game_state.o tge_signals.o
OBJS+=worms_game.o worms_screen.o worms_time.o worms_worm.o worms_food.o

# Source and clean files and globs
SRCS=$(wildcard *.c *.h)

SRCGLOB=*.c

CLNGLOB=$(OUT) $(SAMPLEOUT)
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CFLAGS+=$(C_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CFLAGS+=$(C_RELEASE_FLAGS)
release: main

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# docs - makes Doxygen documentation:
.PHONY: docs
docs:
	@doxygen
	-@cd latex; make; cd ..
	@if [ ! -d docs ]; then \
		mkdir docs; fi
	@echo "Copying reference manual to docs..."
	@cp latex/refman.pdf docs 
	@echo "Done."

# lint - runs splint with specified options
.PHONY: lint
lint:
	@splint +unix-lib -unrecog $(SRCGLOB)

# linteasy - runs splint with weak checking
.PHONY: linteasy
linteasy:
	@splint -weak +unix-lib -unrecog -retvalother -f ./.splintrc $(SRCGLOB)


# Executable targets section
# ==========================

# Main library
main: $(OBJS)
	@echo "Linking worms..."
	@$(CC) -o $(OUT) $(OBJS) $(LDFLAGS)
	@echo "Done."


# Object files targets section
# ============================

main.o: main.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

tge_curses_routines.o: tge_curses_routines.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

tge_main_game.o: tge_main_game.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

tge_signals.o: tge_signals.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

tge_game_state.o: tge_game_state.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

worms_game.o: worms_game.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

worms_food.o: worms_food.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

worms_screen.o: worms_screen.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

worms_time.o: worms_time.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

worms_worm.o: worms_worm.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<


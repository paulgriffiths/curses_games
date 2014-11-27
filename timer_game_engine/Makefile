# Curses Timer Game Engine Makefile
# =================================
# Copyright 2014 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

MKFLPATH    := $(realpath $(lastword $(MAKEFILE_LIST)))
MKFLDIR     := $(dir $(MKFLPATH))
LIBDIR      := $(MKFLDIR)lib
BINDIR      := $(MKFLDIR)bin
INCLDIR     := $(MKFLDIR)include

SOURCES     := $(wildcard src/*.c)
OBJECTS	     = $(subst .c,.o,$(SOURCES))
DEPENDS	     = $(subst .c,.d,$(SOURCES))
LIBRARY     := $(LIBDIR)/libpg_curses_tge.a
SAMPLE		:= $(BINDIR)/sample

AR			:= ar
ARFLAGS		:= rcs
CC          := gcc
CFLAGS      := -std=c99 -pedantic -Wall -Wextra -ggdb -DDEBUG -DDEBUG_ALL
CPPFLAGS	:= -I$(INCLDIR)
LDFLAGS		:= -L$(LIBDIR) -lpg_curses_tge -lcurses
RM          := rm -f
SED         := sed
CTAGS       := ctags

CLNGLOB      = $(LIBRARY) $(OBJECTS) $(DEPENDS) tags

default: all
	
all: $(LIBRARY) $(SAMPLE)

$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

$(SAMPLE): samplesrc/main.c
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

# clean - removes ancilliary files from working directory

.PHONY: clean
clean:
	-@$(RM) $(CLNGLOB) 2>/dev/null

# tags - makes tags file

.PHONY: tags
tags:
	@$(CTAGS) $(SOURCES)

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

# Dependencies

-include $(DEPENDS)

%.d: %.c
	@$(CC) -M $(CFLAGS) $(CPPFLAGS) $< > $@.tmp; \
		$(SED) 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
		$(RM) $@.tmp

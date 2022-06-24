HEADERDIR = include
BUILDDIR = build

V = @

DEBUG = -g
OPTIM = -O3 -march=native -mtune=native
INCLUDEDIR = -I$(HEADERDIR) -ISDL2-2.0.22/include
LIBFLAGS = -lm
CFLAGS = -fpic $(INCLUDEDIR) $(DEBUG) $(OPTIM) -MMD -MP -o $@
CFLAGS += $(shell cat compile_flags.txt | tr '\n' ' ')

CC = gcc

# Source file list
SRCS += src/global.c
SRCS += src/grid.c
SRCS += src/init.c
SRCS += src/main.c
SRCS += src/utilities.c

TESTSRCS += $(wildcard src/tests/*.c)

###

OBJS := $(SRCS:%=$(BUILDDIR)/%.o)
OBJS := $(OBJS:.c.o=.o)
DEPS := $(OBJS:.o=.d)

TESTBINS = $(TESTSRCS:%.c=$(BUILDDIR)/%)
###

.PHONY : all clean __FORCE__

.SUFFIXES :

###

all : $(BUILDDIR)/main
	$V echo "Build complete."

-include $(DEPS)

$(BUILDDIR)/main : $(OBJS) SDL2-2.0.22/build/.libs/libSDL2.a
	$V printf "Linking binary \033[1m$(notdir $@)\033[0m...\n"
	$V $(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $^

SDL2-2.0.22/build/.libs/libSDL2.a : __FORCE__
	$V printf "Fetching and building external library \033[1m$(notdir $@)\033[0m...\n"
	$V [[ -d SDL2-2.0.22 ]] || ./fetch-sdl.sh
	$V (cd SDL2-2.0.22; ./configure)
	$V $(MAKE) -C SDL2-2.0.22

$(BUILDDIR)/%.o : %.c
	$V mkdir -p $(dir $@)
	$V printf "Compiling \033[1m$(notdir $@)\033[0m from $(notdir $<)...\n"
	$V $(CC) $(CFLAGS) -c $<

### 

clean : __FORCE__
	$V rm -rf build/
	$V echo Clean

__FORCE__ :

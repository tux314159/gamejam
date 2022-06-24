HEADERDIR = include
BUILDDIR = build

V = @

DEBUG = -g
OPTIM = -O3 -march=native -mtune=native
INCLUDEDIR = -I$(HEADERDIR)
LIBFLAGS = -lSDL2
CFLAGS = -fpic $(INCLUDEDIR) $(DEBUG) $(OPTIM) -MMD -MP -o $@
CFLAGS += $(shell cat compile_flags.txt | tr '\n' ' ')

CC = gcc

# Source file list
SRCS += src/main.c
SRCS += src/init.c
SRCS += src/grid.c
SRCS += src/geometry.c

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

$(BUILDDIR)/main : $(OBJS)
	$V printf "Linking binary \033[1m$(notdir $@)\033[0m...\n"
	$V $(CC) $(CFLAGS) $(LIBFLAGS) -o $@ $^

$(BUILDDIR)/%.o : %.c
	$V mkdir -p $(dir $@)
	$V printf "Compiling \033[1m$(notdir $@)\033[0m from $(notdir $<)...\n"
	$V $(CC) $(CFLAGS) -c $<

### 

clean : __FORCE__
	$V rm -rf build/
	$V echo Clean

__FORCE__ :

#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "global.h"
#include "pair.h"
#include "utilities.h"

#define GRID_WIDTH 20
#define GRID_HEIGHT 20
#define CELL_W 40
#define CELL_H 40

typedef Entity **Grid;

void init_grid(Grid *grid);

void fill_grid(Grid grid, unsigned int seed);

void disp_grid_sdl(Grid grid);

#endif

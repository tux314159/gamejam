#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "pair.h"
#include "utilities.h"

#define GRID_WIDTH 25
#define GRID_HEIGHT 25
#define GRID_OFFSET_X 0
#define GRID_OFFSET_Y 30
#define CELL_W 40
#define CELL_H 40

void init_grid(Grid *grid);
void destroy_grid(Grid grid);
void fill_grid(Grid grid, unsigned int seed);
void disp_grid_sdl(Grid grid);

#endif

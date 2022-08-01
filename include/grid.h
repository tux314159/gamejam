#ifndef GRID_H
#define GRID_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global.h"
#include "pair.h"
#include "utilities.h"

#define GRID_OFFSET_X 0
#define GRID_OFFSET_Y 30
#define CELL_W 40
#define CELL_H 40

// Initialise up grid
void init_grid(struct Grid *grid, size_t w, size_t h);
// Free memory in grid allocated by init_grid
void destroy_grid(struct Grid grid);
// Randomly fill the grid with shit
void fill_grid(struct Grid grid, unsigned int seed);
// Draw the grid
void disp_grid_sdl(struct Grid grid);

#endif

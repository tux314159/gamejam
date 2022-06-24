#ifndef GRID_H
#define GRID_H

#include <entity.h>
#include <global.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20
#define CELL_W 20
#define CELL_H 20

typedef Entity **Grid;

void init_grid(Grid *grid);

void fill_grid(Grid grid, unsigned int seed);

void disp_grid_sdl(Grid grid);

#endif

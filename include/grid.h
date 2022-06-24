#ifndef GRID_H
#define GRID_H

#include <entity.h>
#include <global.h>

typedef Entity **Grid;

void init_grid(Grid *grid);

void fill_grid(Grid grid, unsigned int seed);

void disp_grid(Grid grid);

#endif

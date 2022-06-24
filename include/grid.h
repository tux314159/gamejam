#ifndef GRID_H
#define GRID_H

#include <entity.h>

typedef Entity **Grid;

void fill_grid(Grid grid, unsigned int seed);

void disp_grid(Grid grid);

#endif

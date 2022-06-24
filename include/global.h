#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL_video.h>
#include <entity.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20

Entity g_grid[GRID_WIDTH][GRID_HEIGHT];
SDL_Window *g_window;

#endif

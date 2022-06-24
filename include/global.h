#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL_video.h>
#include <entity.h>

#define GRID_WIDTH 20
#define GRID_HEIGHT 20

extern Entity **g_grid;
extern SDL_Window *g_window;

#endif

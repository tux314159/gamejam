#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_pixels.h>

#include "base.h"

#define GRID_WIDTH 25
#define GRID_HEIGHT 25

extern struct Grid g_grid;
extern SDL_Window *g_window;
extern SDL_Renderer *g_renderer;
extern Player g_player;
extern unsigned int g_seed;
extern unsigned long long g_tick;
extern SDL_Color sdl_colours[];

#endif

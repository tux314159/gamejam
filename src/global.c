#include "global.h"

Entity **g_grid;
SDL_Window *g_window;
SDL_Renderer *g_renderer;
Player g_player;
unsigned int g_seed;
unsigned long long g_tick;
SDL_Color sdl_colours[] = {
    {255, 255, 255, 255},
    {0, 0, 0, 255},
};

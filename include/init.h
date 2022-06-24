#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include "global.h"

void init_sdl(int w, int h);
void destroy_sdl(SDL_Window *window);

#endif

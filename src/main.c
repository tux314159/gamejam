#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "global.h"
#include "grid.h"
#include "init.h"

int main(int argc, char **argv) {
    bool running = true;

    if (argc < 3) {
        puts("not enough args you dumbass");
        exit(1);
    }

    init_grid(&g_grid);
    fill_grid(g_grid, time(NULL));

    init_sdl(atoi(argv[1]), atoi(argv[2]));
    SDL_RenderPresent(g_renderer);
    disp_grid_sdl(g_grid);

    SDL_Event ev;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }
        SDL_RenderPresent(g_renderer);
        SDL_Delay(10);
    }

    destroy_sdl(g_window);
}

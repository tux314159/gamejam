#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "base.h"
#include "global.h"
#include "grid.h"
#include "init.h"
#include "player.h"

int main(int argc, char **argv) {
    bool running = true;

    if (argc < 3) {
        puts("not enough args you dumbass");
        exit(1);
    }

    init_grid(&g_grid);
    g_seed = time(NULL);
    fill_grid(g_grid, g_seed);

    init_sdl(atoi(argv[1]), atoi(argv[2]));
    SDL_RenderPresent(g_renderer);

    g_player.pos_x = 0;
    g_player.pos_y = 0;

    SDL_Event ev;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    // player movement
                    switch (ev.key.keysym.sym) {
                        case SDLK_UP:
                            g_player = player_move(0, -1, g_player);
                            break;
                        case SDLK_DOWN:
                            g_player = player_move(0, 1, g_player);
                            break;
                        case SDLK_LEFT:
                            g_player = player_move(-1, 0, g_player);
                            break;
                        case SDLK_RIGHT:
                            g_player = player_move(1, 0, g_player);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }
        fill_grid(g_grid, g_seed);
        disp_grid_sdl(g_grid);
        SDL_RenderPresent(g_renderer);
        SDL_Delay(10);
    }

    destroy_sdl(g_window);
}

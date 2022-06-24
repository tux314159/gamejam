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
    g_tick = 0;
    g_player.traits[slowness_trait] = 10;

    init_sdl(atoi(argv[1]), atoi(argv[2]));
    SDL_RenderPresent(g_renderer);
    const unsigned char *kbstate = SDL_GetKeyboardState(NULL);

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
                    switch (ev.key.keysym.sym) {
                        default:
                            break;
                    }
                default:
                    break;
            }

        }

        // player movement
        if (kbstate[SDL_SCANCODE_UP]) {
            g_player = player_move(0, -1, g_player);
        } else if (kbstate[SDL_SCANCODE_DOWN]) {
            g_player = player_move(0, 1, g_player);
        } else if (kbstate[SDL_SCANCODE_LEFT]) {
            g_player = player_move(-1, 0, g_player);
        } else if (kbstate[SDL_SCANCODE_RIGHT]) {
            g_player = player_move(1, 0, g_player);
        }

        fill_grid(g_grid, g_seed);
        disp_grid_sdl(g_grid);
        SDL_RenderPresent(g_renderer);
        SDL_Delay(10);
        g_tick++;
    }

    destroy_sdl(g_window);
}

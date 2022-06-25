#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
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

    // Initialise SDL
    init_sdl(atoi(argv[1]), atoi(argv[2]));
    const unsigned char *kbstate = SDL_GetKeyboardState(NULL);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    TTF_Init();

    // Initialise the rest of the globals
    g_player.pos_x = 0;
    g_player.pos_y = 0;
    g_player.traits[slowness_trait] = 10;
    g_seed = time(NULL);
    g_tick = 0;
    init_grid(&g_grid);
    fill_grid(g_grid, g_seed);

    // Setting up some shit we will need in the...
    SDL_Event ev;
    char *speed_str = calloc(100, sizeof(char));
    TTF_Font* sans_font = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 16);
    // ...Main event loop
    while (running) {
        // Handle events
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

        // Generate grid
        fill_grid(g_grid, g_seed);
        disp_grid_sdl(g_grid);

        // Render text
        sprintf(speed_str, "speed: %d", 16 - g_player.traits[slowness_trait]);
        SDL_Surface* msg_surf = TTF_RenderText_Blended(
                sans_font,
                speed_str,
                sdl_colours[black_col]); 
        SDL_Texture* msg_tex = SDL_CreateTextureFromSurface(g_renderer, msg_surf);
        SDL_Rect msg_rect = {
            .x = 0,
            .y = 0,
            .w = msg_surf->w,
            .h = msg_surf->h,
        };
        SDL_RenderCopy(g_renderer, msg_tex, NULL, &msg_rect);
        SDL_FreeSurface(msg_surf);
        SDL_DestroyTexture(msg_tex);

        // Render etc.
        SDL_RenderPresent(g_renderer);
        SDL_Delay(10);
        g_tick++;
    }

    // Destroy everything
    free(speed_str);
    TTF_CloseFont(sans_font);
    destroy_grid(g_grid);
    destroy_sdl(g_window);
}

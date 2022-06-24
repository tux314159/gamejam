#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "gameloop.h"
#include "global.h"

void gameloop() {
    bool quit = false;
    SDL_Event e;

    Uint64 now       = SDL_GetPerformanceCounter();
    Uint64 last      = 0;
    double deltaTime = 0;

    while (!quit) {
        // calculate deltatime
        last        = now;
        now         = SDL_GetPerformanceCounter();
        double freq = SDL_GetPerformanceFrequency();
        deltaTime   = ((now - last) * 1000 / freq);

        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    g_player.screen_x -=
                        g_player.traits[speed_trait] * deltaTime;
                    break;
                case SDLK_RIGHT:
                    g_player.screen_x +=
                        g_player.traits[speed_trait] * deltaTime;
                    break;
                case SDLK_UP:
                    g_player.screen_y -=
                        g_player.traits[speed_trait] * deltaTime;
                    break;
                case SDLK_DOWN:
                    g_player.screen_y +=
                        g_player.traits[speed_trait] * deltaTime;
                    break;
                }
            }
        }

        SDL_Delay(16);
    }
}

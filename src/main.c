#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include <global.h>
#include <grid.h>
#include <init.h>

int main(int argc, char **argv) {
    SDL_Surface *screensurf;

    init_grid(&g_grid);
    fill_grid(g_grid, 1);
    disp_grid(g_grid);

    (void)argc;

    g_window = init_sdl(atoi(argv[1]), atoi(argv[2]));

    screensurf = SDL_GetWindowSurface(g_window);
    SDL_FillRect(screensurf, NULL,
                 SDL_MapRGB(screensurf->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(g_window);

    SDL_Delay(2000);
}

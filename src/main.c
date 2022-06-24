#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <time.h>

#include <global.h>
#include <grid.h>
#include <init.h>

int main(int argc, char **argv) {
    init_grid(&g_grid);
    fill_grid(g_grid, time(NULL));

    (void)argc;

    init_sdl(atoi(argv[1]), atoi(argv[2]));
    SDL_RenderPresent(g_renderer);
    disp_grid_sdl(g_grid);

    SDL_Delay(2000);
    destroy_sdl(g_window);
}

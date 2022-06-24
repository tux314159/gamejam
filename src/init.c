#include "init.h"

static SDL_Window *init_mainwin(int w, int h) {
    SDL_Window *window =
        SDL_CreateWindow("SDL THINGI", SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created.");
        exit(1);
    }

    return window;
}

static SDL_Renderer *init_mainwin_renderer(void) {
    SDL_Renderer *renderer =
        SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Could not create rendering context.");
        exit(1);
    }

    return renderer;
}

void init_sdl(int w, int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialisation error.");
        exit(1);
    }

    g_window   = init_mainwin(w, h);
    g_renderer = init_mainwin_renderer();

    return;
}

void destroy_sdl(SDL_Window *window) {
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}

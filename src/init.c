#include <init.h>

static SDL_Window *init_mainwin(int w, int h)
{
    SDL_Window *window = SDL_CreateWindow(
            "SDL THINGI",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            w,
            h,
            SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created.");
        exit(1);
    }
    
    return window;
}
 
SDL_Window *init_sdl(int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialisation error.");
        exit(1);
    }

    return init_mainwin(w, h);
}

void destroy_sdl(SDL_Window *window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}

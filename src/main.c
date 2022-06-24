#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

#include <init.h>

int main(int argc, char **argv)
{
    SDL_Window* window = NULL;
    SDL_Surface *screensurf = NULL;
    (void)argc;

    window = init_sdl(atoi(argv[1]), atoi(argv[2]));

    screensurf = SDL_GetWindowSurface(window);
    SDL_FillRect(screensurf, NULL, SDL_MapRGB(screensurf->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    SDL_Delay(2000);
}

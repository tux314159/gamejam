#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    SDL_Window* window = NULL;
    SDL_Surface *screensurf = NULL;
    (void)argc;
    (void)argv;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialisation error");
    }
    (void)window;
    (void)screensurf;
}

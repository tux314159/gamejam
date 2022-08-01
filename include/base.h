#ifndef BASE_H
#define BASE_H

/*
 * Base datatypes for the game; they're all in one
 * file cos they're pretty interdependent
 */

#include <SDL2/SDL_pixels.h>
#define NUM_TRAITS 4

typedef struct {
    int pos_x;
    int pos_y;

    double age;

    int traits[NUM_TRAITS];
} Player;

typedef enum Entity {
    empty_ent    = '.',
    obstacle_ent = '-',
    player_ent   = 'P',
    trap_ent     = 'x',
    potion_ent   = '^',
    monster_ent  = 'M'
} Entity;

typedef enum {
    white_col = 0,
    black_col,
} Colours;

struct Grid {
    size_t w;
    size_t h;
    Entity **egrid; // entity grid
};

#endif

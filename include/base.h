#ifndef BASE_H
#define BASE_H

/*
 * Base datatypes for the game; they're all in one
 * file cos they're pretty interdependent
 */

#define NUM_TRAITS 4

typedef struct {
    int pos_x;
    int pos_y;

    double age;

    int traits[NUM_TRAITS];
} Player;

typedef enum {
    empty_ent    = '.',
    obstacle_ent = '-',
    player_ent   = 'P',
    trap_ent     = 'x',
    potion_ent   = '^',
    monster_ent  = 'M'
} Entity;

typedef Entity **Grid;

#endif

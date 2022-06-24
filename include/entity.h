#ifndef ENTITY_H
#define ENTITY_H

typedef enum {
    empty_ent    = '.',
    obstacle_ent = '-',
    player_ent   = 'P',
    trap_ent     = 'x',
    potion_ent   = '^',
    monster_ent  = 'M'
} Entity;

#endif

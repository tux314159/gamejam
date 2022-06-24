#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "grid.h"

typedef enum {
    slowness_trait,
    view_radius_trait,
    strength_trait,
    wisdom_trait,
} Trait;

Player player_move(int dx, int dy, Player p);

#endif

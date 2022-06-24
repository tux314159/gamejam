#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

#define NUM_TRAITS 4
typedef enum {
    speed_trait,
    view_radius_trait,
    strength_trait,
    wisdom_trait,
} Trait;

typedef struct {
    float screen_x;
    float screen_y;

    float age;

    float traits[NUM_TRAITS];

} Player;

#endif

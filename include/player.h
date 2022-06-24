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
    double screen_x;
    double screen_y;

    double age;

    double traits[NUM_TRAITS];

} Player;

#endif

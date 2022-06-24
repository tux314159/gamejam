#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int width;
    int height;
} GridRect;

bool rect_rect_intersect(GridRect r1, GridRect r2);

#endif

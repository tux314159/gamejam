#include <entity.h>
#include <geometry.h>
#include <global.h>
#include <grid.h>
#include <pair.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_grid(Grid *grid) {
    grid = malloc(GRID_HEIGHT * sizeof(Entity *));
    for (int i = 0; i < GRID_HEIGHT; i++) {
        grid[i] = malloc(GRID_WIDTH * sizeof(Entity));
    }
}

void fill_grid(Grid *grid, unsigned int seed) {
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            *grid[i][j] = empty_ent;

    *grid[0][0] = player_ent; // player starts at top left corner

    srand(seed);

    // each potion looks like this
    // . . .
    // . ^ .
    // . M .
    static const int POTION_PLACE_SIZE                               = 3;
    static const int NUM_POTION_PLACES                               = 4;
    static Entity POTION_PLACE[POTION_PLACE_SIZE][POTION_PLACE_SIZE] = {
        {obstacle_ent, obstacle_ent, obstacle_ent},
        {obstacle_ent, potion_ent, obstacle_ent},
        {obstacle_ent, monster_ent, obstacle_ent}};

    GridRect potion_places[NUM_POTION_PLACES];

    // generate the potion places
    for (int i = 0; i < NUM_POTION_PLACES; i++) {
        bool is_overlapping = false;
        GridRect potion_place_rect;
        do {
            int x = rand() % (GRID_WIDTH - POTION_PLACE_SIZE);
            int y = rand() % (GRID_HEIGHT - POTION_PLACE_SIZE);

            potion_place_rect.x      = x;
            potion_place_rect.y      = y;
            potion_place_rect.width  = POTION_PLACE_SIZE;
            potion_place_rect.height = POTION_PLACE_SIZE;

            // check for overlaps
            for (int j = 0; j < i; j++) {
                is_overlapping |=
                    rect_rect_intersect(potion_place_rect, potion_places[j]);
            }
        } while (!is_overlapping);

        // copy over the "template" POTION_PLACE into grid
        for (int j = 0; j < POTION_PLACE_SIZE; j++) {
            for (int k = 0; k < POTION_PLACE_SIZE; k++) {
                int y       = j + potion_place_rect.y;
                int x       = k + potion_place_rect.x;
                *grid[y][x] = POTION_PLACE[j][k];
            }
        }

        // store it in potion_places for future overlap checks
        potion_places[i] = potion_place_rect;
    }
}

void disp_grid(Grid *grid) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            printf("%c", *grid[i][j]);
        }
        printf("\n");
    }
}

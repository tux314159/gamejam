#include <entity.h>
#include <global.h>
#include <grid.h>
#include <pair.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utilities.h>

#define POTION_PLACE_SIZE 3
#define NUM_POTION_PLACES 4

void init_grid(Grid *grid) {
    *grid = malloc(GRID_HEIGHT * sizeof(**grid));
    for (int i = 0; i < GRID_HEIGHT; i++) {
        (*grid)[i] = malloc(GRID_WIDTH * sizeof(***grid));
    }
}

void fill_grid(Grid grid, unsigned int seed) {
    srand(seed);

    // {{{ #0 fill this with empty entities first
    for (int i = 0; i < GRID_HEIGHT; i++)
        for (int j = 0; j < GRID_WIDTH; j++)
            grid[i][j] = empty_ent;
    // }}}

    // {{{ #1 player starts at top left corner
    grid[0][0] = player_ent;
    // }}}

    // {{{ #2 generate the potion places

    // each potion looks like this
    // - - -
    // - ^ -
    // - M -
    static Entity POTION_PLACE[POTION_PLACE_SIZE][POTION_PLACE_SIZE] = {
        {obstacle_ent, obstacle_ent, obstacle_ent},
        {obstacle_ent, potion_ent, obstacle_ent},
        {obstacle_ent, monster_ent, obstacle_ent}};

    Pair potion_place_entrances[NUM_POTION_PLACES];

    for (int i = 0; i < NUM_POTION_PLACES; i++) {
        while (1) {
            bool is_overlapping = false;

            int x = rand() % (GRID_WIDTH - POTION_PLACE_SIZE);
            int y = rand() % (GRID_HEIGHT - POTION_PLACE_SIZE - 1);

            // printf("%d %d %d\n", i, x, y);
            // disp_grid(grid);

            // check for overlaps
            for (int j = 0; j < POTION_PLACE_SIZE; j++) {
                for (int k = 0; k < POTION_PLACE_SIZE; k++) {
                    is_overlapping |= (grid[y + j][x + k] != empty_ent);
                }
            }

            if (!is_overlapping) {
                // copy over the "template" POTION_PLACE into grid
                for (int j = 0; j < POTION_PLACE_SIZE; j++) {
                    for (int k = 0; k < POTION_PLACE_SIZE; k++) {
                        grid[y + j][x + k] = POTION_PLACE[j][k];

                        if (POTION_PLACE[j][k] == monster_ent) {
                            potion_place_entrances[i].first  = x;
                            potion_place_entrances[i].second = y + 1;
                        }
                    }
                }
                break;
            }
        }
    }
    // }}}

    // {{{ #3 Add some obstacles
    // }}}

    // {{{ #4 fill it with booby traps
    const int NUM_TRAPS = rand_range(6, 15);
    for (int i = 0; i < NUM_TRAPS; i++) {
        bool can_place_trap = false;
        do {
            int x = rand_range(0, GRID_WIDTH - 1);
            int y = rand_range(0, GRID_HEIGHT - 1);

            // check that its not blocking the entrance to a potion place
            bool is_blocking = false;
            for (int j = 0; j < NUM_POTION_PLACES; j++) {
                is_blocking |= potion_place_entrances[j].first == x &&
                               potion_place_entrances[j].second == y;
            }

            if (grid[y][x] == empty_ent && !is_blocking) {
                can_place_trap = true;
                // actually put this in the grid
                grid[y][x] = trap_ent;
            }
        } while (!can_place_trap);
    }
    // }}}
}

void disp_grid(Grid grid) {
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

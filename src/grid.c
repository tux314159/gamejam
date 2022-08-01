#include "grid.h"

#define POTION_PLACE_SIZE 3
#define NUM_POTION_PLACES 4

void init_grid(struct Grid *grid, size_t w, size_t h) {
    enum Entity **egrid;
    egrid = malloc(h * sizeof(*egrid));
    for (size_t i = 0; i < h; i++) {
        egrid[i] = malloc(w * sizeof(**egrid));
    }

    grid->w     = w;
    grid->h     = h;
    grid->egrid = egrid;
    return;
}

void destroy_grid(struct Grid grid) {
    for (size_t i = 0; i < grid.h; i++) {
        free(grid.egrid[i]);
    }
    free(grid.egrid);
}

void fill_grid(struct Grid grid, unsigned int seed) {
    srand(seed);

    const int dx[] = {0, 0, 1, -1};
    const int dy[] = {1, -1, 0, 0};

    // {{{ #0 fill this with empty entities first
    for (size_t i = 0; i < grid.h; i++)
        for (size_t j = 0; j < grid.w; j++)
            grid.egrid[i][j] = empty_ent;
    // }}}

    // {{{ #1 draw the player
    grid.egrid[g_player.pos_y][g_player.pos_x] = player_ent;
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
        for (;;) {
            bool is_overlapping = false;

            int x = rand() % ((long long)grid.w - POTION_PLACE_SIZE);
            int y = rand() % ((long long)grid.h - POTION_PLACE_SIZE - 1);

            // printf("%d %d %d\n", i, x, y);
            // disp_grid(grid);

            // check for overlaps
            for (int j = 0; j < POTION_PLACE_SIZE; j++) {
                for (int k = 0; k < POTION_PLACE_SIZE; k++) {
                    is_overlapping |= (grid.egrid[y + j][x + k] != empty_ent);
                }
            }

            if (!is_overlapping) {
                // copy over the "template" POTION_PLACE into grid
                for (int j = 0; j < POTION_PLACE_SIZE; j++) {
                    for (int k = 0; k < POTION_PLACE_SIZE; k++) {
                        grid.egrid[y + j][x + k] = POTION_PLACE[j][k];

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
    const int num_walls = rand_range(6, 15);
    for (int i = 0; i < num_walls; i++) {
        long long x     = rand_range(0, grid.w - 1);
        long long y     = rand_range(0, grid.h - 1);
        int dir         = rand_range(0, 3);
        int wall_length = rand_range(3, 10);
        // printf("%d %d %d %d\n", x, y, dir, wall_length);
        for (int j = 0;
             j < wall_length && x >= 0 && x < (long long)grid.w && y >= 0 &&
             y < (long long)grid.h && grid.egrid[x][y] == empty_ent;
             j++) {
            grid.egrid[x][y] = obstacle_ent;
            x += (unsigned)dx[dir];
            y += (unsigned)dy[dir];
        }
    }
    // }}}

    // {{{ #4 fill it with booby traps
    const int num_traps = rand_range(6, 15);
    for (int i = 0; i < num_traps; i++) {
        bool can_place_trap = false;
        do {
            int x = rand_range(0, grid.w - 1);
            int y = rand_range(0, grid.h - 1);

            // check that its not blocking the entrance to a potion place
            bool is_blocking = false;
            for (int j = 0; j < NUM_POTION_PLACES; j++) {
                is_blocking |= potion_place_entrances[j].first == x &&
                               potion_place_entrances[j].second == y;
            }

            if (grid.egrid[y][x] == empty_ent && !is_blocking) {
                can_place_trap = true;
                // actually put this in the grid
                grid.egrid[y][x] = trap_ent;
            }
        } while (!can_place_trap);
    }
    // }}}
}

static SDL_Texture *bmp2texture(const char *fname) {
    SDL_Surface *wall_h_s = SDL_LoadBMP(fname);
    SDL_Texture *wall_h   = SDL_CreateTextureFromSurface(g_renderer, wall_h_s);
    SDL_FreeSurface(wall_h_s);
    return wall_h;
}

#define SPRITEDIR "assets/gridsprites/"
#define MKSPRITE(name, ...)                                                    \
    do {                                                                       \
        SDL_Texture *name##_tex = bmp2texture(SPRITEDIR #name ".bmp");         \
        {__VA_ARGS__};                                                         \
        SDL_DestroyTexture(name##_tex);                                        \
    } while (0);

void disp_grid_sdl(struct Grid grid) {
    // Initialise our textures (sprites)
    MKSPRITE(
        player,
        MKSPRITE(
            wall,
            MKSPRITE(
                potion,

                SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
                SDL_RenderClear(g_renderer);

                for (size_t i = 0; i < grid.h; i++) {
                    for (size_t j = 0; j < grid.w; j++) {
                        struct SDL_Rect r = {
                            .x = CELL_W * j + GRID_OFFSET_X,
                            .y = CELL_H * i + GRID_OFFSET_Y,
                            .w = CELL_W,
                            .h = CELL_H,
                        };
                        switch (grid.egrid[i][j]) {
                        case empty_ent:
                            break;
                        case player_ent:
                            SDL_RenderCopy(g_renderer, player_tex, NULL, &r);
                            break;
                        case obstacle_ent:
                            SDL_RenderCopy(g_renderer, wall_tex, NULL, &r);
                            break;
                        case potion_ent:
                            SDL_RenderCopy(g_renderer, potion_tex, NULL, &r);
                            break;
                        default:
                            // for now
                            SDL_RenderCopy(g_renderer, wall_tex, NULL, &r);
                            break;
                        }
                    }
                })));
    return;
}

#include "player.h"

Player player_move(int dx, int dy, Player p) {
    int n_pos_x = p.pos_x + dx;
    int n_pos_y = p.pos_y + dy;
    if (n_pos_x >= 0 && n_pos_y >= 0 && n_pos_x < GRID_WIDTH &&
        n_pos_y < GRID_HEIGHT && g_grid.egrid[n_pos_y][n_pos_x] == empty_ent &&
        g_tick % (unsigned long long)p.traits[slowness_trait] == 0) {
        p.pos_x = n_pos_x;
        p.pos_y = n_pos_y;
    }

    return p;
}

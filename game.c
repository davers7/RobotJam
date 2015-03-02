#include "game.h"

#include "sprites.h"
#include "utils.h"

void start_new_game(game_data *gd) {
    unsigned char i;

    // Empty the board
    i = 0;
    while (i < BOARD_SIZE) {
        unsigned char j = 0;
        while (j < BOARD_SIZE / 8) {
            gd->board[i][j] = 0;
            ++j;
        }
        ++i;
    }

    // Free the slots
    i = 0;
    while (i < BULLET_MAX / 8) {
        gd->bullet_slots[i] = 0;
        ++i;
    }

    // Set the player 1
    gd->players[0].posx = 0;
    gd->players[0].posy = 0;
    gd->players[0].health = HEALTH_MAX;
    gd->players[0].ammo_cooldown = AMMO_COOLDOWN;

    // Set the player 2
    gd->players[1].posx = BOARD_SIZE - SPRITE_PLAYER_SIZE - 1;
    gd->players[1].posy = BOARD_SIZE - SPRITE_PLAYER_SIZE - 1;
    gd->players[1].health = HEALTH_MAX;
    gd->players[1].ammo_cooldown = AMMO_COOLDOWN;
}

void update_state(game_data *gd) {
    update_players(gd);
    update_bullets(gd);
}

void update_players(game_data *gd) {

}

void update_bullets(game_data *gd) {
    unsigned char i = 0;
    while (i < BULLET_MAX) {
        unsigned char bi = i % 8; // TODO: remove modulo

        // Is there a bullet?
        if (bitn(gd->bullet_slots[i], bi)) {
            unsigned char new_x = gd->bullets[i].posx + gd->bullets[i].velx;
            unsigned char new_y = gd->bullets[i].posy + gd->bullets[i].vely;

            // Check if new position is in limits
            if (new_x >= BOARD_SIZE || new_y >= BOARD_SIZE) {
                // Remove projectile
                gd->bullet_slots[i / 8] &= ~(1 << bi);

                // Check other projectiles if any
                goto next_projectile;
            }

            // Check if there is collision
            if (bitn(gd->board[new_y][new_x / 8], new_x % 8)) {
                unsigned char j;

                // This is very inefficient but we don't have much memory...
                // Check both players
                j = 0;
                while (j < 2) {
                    if ((gd->players[j].posx == new_x) &&
                        (gd->players[j].posy == new_y)) {
                        // Remove projectile
                        gd->bullet_slots[i / 8] &= ~(1 << bi);

                        // Player loses 1 health point
                        if (!--gd->players[j].health) {
                            // Player is dead
                            // TODO: other player wins
                        }

                        // Check other projectiles if any
                        goto next_projectile;
                    }
                    ++j;
                }

                // Loop in projectiles
                j = 0;
                while (j < BULLET_MAX) {
                    unsigned char bj = j % 8; // TODO: remove modulo
                    if (bitn(gd->bullet_slots[j], bj)) {
                        if ((gd->bullets[j].posx == new_x) &&
                            (gd->bullets[j].posy == new_y)) {
                            // Remove both projectiles
                            gd->bullet_slots[i / 8] &= ~(1 << bi);
                            gd->bullet_slots[j / 8] &= ~(1 << bj);

                            // Check other projectiles if any
                            goto next_projectile;
                        }
                    }
                    ++j;
                }

                // Then, there is a wall
                // Remove projectile
                gd->bullet_slots[i / 8] &= ~(1 << bi);

                // Destroy the wall
                gd->board[new_y][new_x / 8] &= ~(1 << new_x % 8);
            } else {
                // No collision, just update its position
                // Unmark the board
                gd->board[gd->bullets[i].posy][gd->bullets[i].posx / 8] &= ~(1 << gd->bullets[i].posx % 8);

                // New position
                gd->bullets[i].posx = new_x;
                gd->bullets[i].posy = new_y;

                // Mark the board
                gd->board[new_y][new_x / 8] |= 1 << new_x % 8;
            }
        }
next_projectile:
        ++i;
    }
}

void place_wall(game_data *gd, unsigned char x, unsigned char y) {
    unsigned char i = 0;
    while (i < WALL_SIZE) {
        unsigned char j = 0;
        while (j < WALL_SIZE) {
            unsigned char x2 = x + j;
            unsigned char y2 = y + i;
            if (x2 < BOARD_SIZE && y2 < BOARD_SIZE) {
                // pas sûr...
                gd->board[y2][x2 / 8] |= 1 << x2 % 8; // TODO: remove modulo
            }
            ++j;
        }
        ++i;
    }
}

void shoot_bullet(game_data *gd, unsigned char x, unsigned char y, char velx, char vely) {
    unsigned char i, j, tmp;

    // Find first free slot
    i = 0;
    while (i < BULLET_MAX / 8) {
        if (gd->bullet_slots[i] != 0b11111111) {
            // Found it (only one bit at free position is set in tmp)
            tmp = ~gd->bullet_slots[i] & (gd->bullet_slots[i] + 1);
            break;
        }
    }

    // No free slot
    if (i == BULLET_MAX / 8) {
        return;
    }

    // Set the slot as used
    gd->bullet_slots[i] |= tmp;

    // Find position of the set bit
    j = 0;
    while (tmp != 1) {
        tmp >>= 1;
        ++j;
    }

    // Set the bullet infos
    gd->bullets[i * 8 + j].posx = x;
    gd->bullets[i * 8 + j].posy = y;
    gd->bullets[i * 8 + j].velx = velx;
    gd->bullets[i * 8 + j].vely = vely;

    // Mark the board
    gd->board[y][x / 8] |= 1 << x % 8;
}

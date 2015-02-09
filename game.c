#include "game.h"

#include "sprites.h"

void start_new_game(game_data *gd) {
    unsigned char i;

    // Empty the board
    i = 0;
    while (i < BOARD_SIZE) {
        unsigned char j = 0;
        while (j < (BOARD_SIZE >> 3)) {
            gd->board[i][j] = 0;

            ++j;
        }

        ++i;
    }

    // Free the slots
    i = 0;
    while (i < (BULLET_MAX >> 3)) {
        gd->bullet_slots[i] = 0;

        ++i;
    }

    // Set the player 1
    gd->player1.posx = 0;
    gd->player1.posy = 0;
    gd->player1.health = HEALTH_MAX;
    gd->player1.ammo_cooldown = AMMO_COOLDOWN;

    // Set the player 2
    gd->player2.posx = BOARD_SIZE - SPRITE_PLAYER_SIZE - 1;
    gd->player2.posy = BOARD_SIZE - SPRITE_PLAYER_SIZE - 1;
    gd->player2.health = HEALTH_MAX;
    gd->player2.ammo_cooldown = AMMO_COOLDOWN;
}

void update_state(game_data *gd) {

}

void place_wall(game_data *gd, char x, char y) {
    unsigned char i = 0;
    while (i < WALL_SIZE) {
        unsigned char j = 0;
        while (j < WALL_SIZE) {
            unsigned char x2 = x + j;
            unsigned char y2 = y + i;
            if (x2 >= 0 && x2 < BOARD_SIZE && y2 >= 0 && y2 < BOARD_SIZE) {
                gd->board[x2][y2] = 1;
            }

            ++j;
        }

        ++i;
    }
}

void shoot_bullet(game_data *gd, char x, char y, char velx, char vely) {

}

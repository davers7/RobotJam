#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "bullet_data.h"
#include "player_data.h"

// Size of the board
#define BOARD_SIZE 128 // multiple of 8, less than 128

// Max number of bullets on the board
#define BULLET_MAX 32 // multiple of 8, less than 256

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE / 8]; // 1 if occupied, 0 otherwise ([y][x])
    player_data players[2];
    bullet_data bullets[BULLET_MAX];
    char bullet_slots[BULLET_MAX / 8]; // 1 if used, 0 otherwise
} game_data;

#endif // _GAME_DATA_H_

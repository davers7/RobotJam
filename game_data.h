#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_

#include "bullet_data.h"
#include "player_data.h"

// Size of the board
#define BOARD_SIZE 128 // multiple of 8

// Max number of bullets on the board
#define BULLET_MAX 32 // multiple of 8

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE >> 3];
    player_data player1, player2;
    bullet_data bullets[BULLET_MAX];
    char bullet_slots[BULLET_MAX >> 3]; // 1 if used, 0 otherwise
} game_data;

#endif // _GAME_DATA_H_

#ifndef _GAME_H_
#define _GAME_H_

#include "game_data.h"

#define WALL_SIZE 5

// Initializes everything for a new game
void start_new_game(game_data *gd);

// Updates the state of the game
void update_state(game_data *gd);

// Places a wall
void place_wall(game_data *gd, char x, char y);

// Shoots a bullet
void shoot_bullet(game_data *gd, char x, char y, char velx, char vely);

#endif // _GAME_H_

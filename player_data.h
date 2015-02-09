#ifndef _PLAYER_DATA_H_
#define _PLAYER_DATA_H_

#define HEALTH_MAX 3
#define AMMO_COOLDOWN 20

typedef struct {
    unsigned char posx, posy;
    unsigned char health;
    unsigned char ammo_cooldown;
} player_data;

#endif // _PLAYER_DATA_H_

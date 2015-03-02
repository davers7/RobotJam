#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "sprites.h"
#include "utils.h"

void display_sprite(unsigned char size, char sprite[]);

int main(int argc, char *argv[]) {
    game_data gd;
    start_new_game(&gd);


    return EXIT_SUCCESS;
}

void display_sprite(unsigned char size, char sprite[]) {
    unsigned char i = 0;
    while (i < size) {
        unsigned char j = 0;
        while (j < size) {
            if (bitn(sprite[i], 7 - j)) {
                printf("x");
            } else {
                printf(" ");
            }
            ++j;
        }
        printf("\n");
        ++i;
    }
}

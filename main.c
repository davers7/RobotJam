#include <stdio.h>
#include <stdlib.h>

#include "sprites.h"
#include "utils.h"

void display_sprite(unsigned char size, char sprite[]);

int main(int argc, char *argv[]) {
    display_sprite(SPRITE_PLAYER_SIZE, sprite_player);
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

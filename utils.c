#include "utils.h"

char bitn(char byte, unsigned char n) {
    return (byte >> n) & 1;
}

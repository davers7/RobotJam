#include "utils.h"

char bitn(char byte, char n) {
    return (byte >> n) & 1;
}

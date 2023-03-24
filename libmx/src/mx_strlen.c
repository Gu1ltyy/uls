#include "libmx.h"

int mx_strlen(const char *s) {
    int length = 0;

    while (*s) {
        ++s;
        length++;
    }

    return length;
}


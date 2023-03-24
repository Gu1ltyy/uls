#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    if (!str || !*str || !sub || !*sub) 
        return -2;

    int index = 0;
    int length = mx_strlen(sub);

    while (*str) {
        if (mx_strncmp(str++, sub, length) == 0)
            return index;
        index++;
    }

    return -1;
}


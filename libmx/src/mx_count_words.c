#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (!str || !*str)
        return -1;
    
    bool state = true;
    int i = 0;
    int j = 0;

    while (str[i]) {
        if (str[i] == c)
            state = true;
        else if (state) {
            state = false;
            j++;
        }

        i++;
    }

    return j;
}


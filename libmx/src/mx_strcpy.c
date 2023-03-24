#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    int ind = 0;

    while (src[ind] != '\0') {
        dst[ind] = src[ind];
        ind++;
    }    

    dst[ind] = '\0';
    return dst;
}


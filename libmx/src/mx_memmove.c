#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *temp = malloc(len);

    temp = mx_memcpy(temp, src, len);
    dst = mx_memcpy(dst, temp, len);
    free(temp);
    temp = NULL;
    
    return dst;
}


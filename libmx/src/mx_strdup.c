#include "libmx.h"

char *mx_strdup(const char *s1) {
    int size = mx_strlen(s1);

    if (size < 0)
        return NULL;
    char *dst = mx_strnew(size);
    mx_strcpy(dst, s1);

    return dst;
}


#include "libmx.h"

char *mx_strstr(const char *s1, const char *s2) {
    char *temp_s1 = (char *)s1;
    char *temp_s2 = (char *)s2;

    if ((!s1) || (!s2))
        return NULL;
    
    if (!mx_strlen(s2))
        return temp_s1;

    while (*temp_s1) {
        if (!mx_strncmp(temp_s1, temp_s2, mx_strlen(temp_s2)))
            return temp_s1;
        temp_s1++;
    }

    return NULL;
}


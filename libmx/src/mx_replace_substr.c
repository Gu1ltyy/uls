#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace || mx_strlen(str) <= mx_strlen(sub))
        return NULL;

    int rep = mx_strlen(replace) - mx_strlen(sub);
    int len = mx_strlen(str) + mx_count_substr(str, sub) * rep;
    char *mem = mx_strnew(len);

    for (int i = 0; i < len; i++, str++) {
        if (!mx_strncmp((char *)str, (char * )sub, mx_strlen(sub))) {
            str += mx_strlen(sub);
            for (int j = 0; j < mx_strlen(replace); j++, i++)
                mem[i] = replace[j];
        }
        mem[i] = *str;
    }

    return mem;
}


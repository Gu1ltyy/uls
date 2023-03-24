#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    if (!str || !*str)
        return NULL;

    char *temp_mem = mx_strnew(mx_strlen(str));
    char *res = NULL;
    int i = 0;
    int j = 0;

    while (str[i]) {
        if (!(mx_isspace(str[i])))
            temp_mem[j++] = str[i];

        if (!mx_isspace(str[i]) && mx_isspace(str[i + 1]))
            temp_mem[j++] = ' ';

        i++;
    }
    res = mx_strtrim(temp_mem);
    mx_strdel(&temp_mem);
    
    return res;
}


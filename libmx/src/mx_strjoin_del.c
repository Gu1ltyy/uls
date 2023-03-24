#include "libmx.h"

char *mx_strjoin_del(char const *s1, char const *s2) {
    if (s1 == NULL)
        return mx_strdup(s2);
    else if (s2 == NULL)
        return mx_strdup(s1);
    else if (s1 == NULL && s2 == NULL)
        return NULL;

    char *res = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    res = mx_strcpy(res, s1);
    res = mx_strcat(res, s2);
    char *del = (char*)s1;
    mx_strdel(&del);
    return res;
}


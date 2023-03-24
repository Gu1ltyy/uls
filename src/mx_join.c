#include "header.h"

void mx_join(char **res, char *s2) {
    char *newstr = mx_strnew(mx_strlen(*res) + mx_strlen(s2));
    int i = 0;
    int sec_i = -1;
    char *s1 = *res;

    for (; s1[++sec_i]; i++) {
        newstr[i] = s1[sec_i];
    }

    for (sec_i = -1; s2[++sec_i]; i++) {
        newstr[i] = s2[sec_i];
    }

    mx_strdel(&(*res));
    *res = newstr;
}

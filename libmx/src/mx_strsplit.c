#include "libmx.h"

char **mx_strsplit(char const *s, char c) {
    if (!s || !*s)
        return NULL;

    char **arr = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char *));
    const char *temp;
    int count = 0;
    int length;

    while ((*s) && (*s != '\0')) {
        length = 0;
        if (*s != c) {
            temp = s;
            while (temp[length] && temp[length] != c)
                length++;
            arr[count] = mx_strndup(s, length);
            s += length;
            count++;
            continue;
        }
        s++;
    }
    arr[count] = NULL;

    return arr;
}


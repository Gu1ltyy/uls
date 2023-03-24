#include "libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    if (buf_size == 0)
        return -2;
    
    buf_size = 1;
    char *lineptr_copy = *lineptr;
    char *temp = mx_strnew(1);
    int res = 0;
    int value;
    *lineptr = NULL;

    while ((value = read(fd, temp, buf_size)) > 0) {
        if (mx_get_char_index(temp, delim) < 0) {
            *lineptr = mx_strjoin_del(*lineptr, temp);
            res += value;
        }
        else {
            temp[mx_get_char_index(temp, delim)] = '\0';
            *lineptr = mx_strjoin_del(*lineptr, temp);
            res += mx_strlen(temp);
            free(temp);
            free(lineptr_copy);
            return res;
        }
    }

    free(temp);

    if (res == 0) {
        *lineptr = lineptr_copy;
        if (value > 0)
            return -1;
        else
            return -2;
    }

    return res;
}


#include "libmx.h"

static int get_len(const char *file) {
    int length = 0;
    char buf[1];

    if (!file)
        return -1;

    int our_file = open(file, O_RDONLY);
    if (our_file < 0)
        return -1;

    while (read(our_file, buf, 1))
        length++;
    if (close(our_file) < 0)
        return -1;

    return length;
}

char *mx_file_to_str(const char *file) {
    int our_file = -1;
    int len = 0;
    int i = 0;
    char buf[1];
    char *str = NULL;

    len = get_len(file);
    if (len >= 0) {
        str = mx_strnew(len);
        if (!str)
            return NULL;

        our_file = open(file, O_RDONLY);
        if (our_file < 0)
            return NULL;

        while (read(our_file, buf, 1))
            str[i++] = buf[0];

        if (close(our_file) < 0)
            return NULL;
    }

    return str;
}


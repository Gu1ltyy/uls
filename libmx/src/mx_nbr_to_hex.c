#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    unsigned long temp_nbr = nbr;
    long length = 0;

    while (temp_nbr) {
        temp_nbr /= 16;
        length++;
    }

    if (length < 0)
        return NULL;

    char *res = malloc(length);
    if (nbr == 0)
        return mx_strcpy(res, "0");

    while (nbr) {
        int ch = nbr % 16;

        if (ch < 10)
            res[--length] = ch + 48;
        if (ch >= 10)
            res[--length] = ch + 55 + 32;

        nbr /= 16;
    }

    return res;
}


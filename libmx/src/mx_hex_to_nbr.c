#include "libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (!hex)
        return 0;

    long length = 0;
    long res = 0;
    long temp;
    long i = 0;
    long value;

    while (hex[length] != '\0')
        length++;

    length--;

    while (hex[i] != '\0') {
        if (mx_isdigit(hex[i]))
            value = hex[i] - 48;
        else if (mx_isalpha(hex[i])) {
            if (mx_isupper(hex[i]))
                value = hex[i] - 65 + 10;
            if (mx_islower(hex[i]))
                value = hex[i] - 97 + 10;
        }
        else
            return 0;
        
        temp = 1;
        for (long j = 0; j < length; j++) 
            temp *= 16;
        
        res += value * temp;
        length--;
        i++;
    }

    return res;
}


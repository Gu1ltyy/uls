#include "libmx.h"

bool mx_islower(int c) {
    if (c >= 65 && c <= 90)
        return false;
    else
        return true;
}


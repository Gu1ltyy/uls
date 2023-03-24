#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    int first = 0;
    int mid;
    int last = size - 1;

    if (!*arr)
        return -1;
    while (first <= last) {
        (*count)++;
        mid = (first + last) / 2;
        if (mx_strcmp(arr[mid], s) == 0)
            return mid;
        else if (mx_strcmp(arr[mid], s) < 0)
            first = mid + 1;
        else
            last = mid - 1;
    }
    
    *count = 0;
    return -1;
}


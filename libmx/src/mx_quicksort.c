#include "libmx.h"

int mx_quicksort(char **arr, int left, int right) {
    if (!arr)
        return -1;
    
    char *pivot;
    char *temp;
    int counter = 0;
    int i;
    int j;

    if (left < right) {
        pivot = arr[(left + right) / 2];
        i = left;
        j = right;
        while (i <= j) {
            while (mx_strlen(arr[i]) < mx_strlen(pivot))
                i++;
            while (mx_strlen(arr[j]) > mx_strlen(pivot))
                j--;

            if (i <= j) {
                if (mx_strlen(arr[i]) != mx_strlen(arr[j])) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                    counter++;
                }
                i++;
                j--;
            }
        }
        counter += mx_quicksort(arr, i, right);
        counter += mx_quicksort(arr, left, j);
    }

    return counter;
}


#include "libmx.h"

char *mx_strcat(char *s1, const char *s2) {
    int str1_size = mx_strlen(s1);
    int str2_size = mx_strlen(s2);
    int i = str1_size;
    int j = 0;

    while (i < (str1_size + str2_size)) {
        s1[i] = s2[j];
        i++;
        j++;
    } 
    
    s1[i++] = '\0';
    return s1;
}


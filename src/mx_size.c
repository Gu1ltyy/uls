#include "header.h"

char *mnr_hex(char *mnr) {
    char *res = mx_strdup("0x00000000");
    int len = mx_strlen(mnr);
    
    mx_strcpy(res + (10 - len), mnr);
    mx_strdel(&mnr);
    return res;
}

char *minor_number(t_obj *objects) {
    int res_numb = (int)(objects->info.st_rdev & 0xffffff);
     if (res_numb <= 255) {
         return mx_itoa(res_numb);
     }
     else {
         return mnr_hex(mx_nbr_to_hex(res_numb));
     }
}

void output_inf(t_size *size, t_obj *objects) {
    char *mjr = mx_itoa((int)(((unsigned int)objects->info.st_rdev >> 24) & 0xff));
    char *mnr = minor_number(objects);
    int mjr_len = mx_strlen(mjr);
    int mnr_len = mx_strlen(mnr);
    
    if (size->is_dev == false)
        mx_printint(objects->info.st_size);
    else {
        if (!IS_BLK(objects->info.st_mode) || !IS_CHR(objects->info.st_mode)) {
            mx_printstr("       ");
            mx_printint(objects->info.st_size);
        }
        else {
            int spaces = 2 - mjr_len;
            int i = 0;
            while (i <= spaces) {
                mx_printchar(' ');
                i++;
            }
            mx_printstr(mjr);
            mx_printchar(',');
            mx_printchar(' ');
            spaces = 2 - mnr_len;
            i = 0;
            while (i <= spaces) {
                mx_printchar(' ');
                i++;
            }
            mx_printstr(mnr);
        }
    }
    free(mjr);
    free(mnr);
}

void mx_size_show(t_size *size, t_obj *objects) {
    int temp_len = 0;
    char *tmp_size = mx_itoa(objects->info.st_size);
    char *f_size = mx_itoa(size->size);
    int temp_size = mx_strlen(tmp_size);
    int final_size = mx_strlen(f_size);
    
    if (temp_size < final_size) {
        for (temp_len = temp_size; temp_len != final_size; temp_len++) {
            mx_printchar(' ');
        }
        output_inf(size, objects);
    }
    else {
        output_inf(size, objects);
    }
    mx_printchar(' ');
    free(tmp_size);
    free(f_size);
}

#include "header.h"

int len_found(t_obj **objs) {
    int res = 0;
    int point = 0;
    
    int i = 0;
    while (objs[i]) {
        point = mx_strlen(objs[i]->name);
        if (point > res) {
            res = point;
        }
        i++;
    }
    res++;
    return res;
}

void space_print(int len, int len_max) {
    int numbr = 0;
    
    numbr = len_max - len;
    int i = 0;
    while (i < numbr) {
        mx_printchar(' ');
        i++;
    }
}

void show_g_row(t_obj **objs, int len_max) {
    int i = 0;
    int len = 0;
    while (objs[i]) {
        mx_g_print(objs[i]);
        if (objs[i + 1]) {
            len = mx_strlen(objs[i]->name);
            space_print(len, len_max);
        }
        i++;
    }
}

void show_c_cols(t_obj **objs, int rows, int count, int len_max) {
    int len = 0;
    int i = 0;
    int j = 0;
    while (i < rows) {
        while (i + j < count) {
            mx_g_print(objs[i + j]);
            if ((i + j + rows < count) && objs[i + j + 1]) {
                len = mx_strlen(objs[i + j]->name);
                space_print(len, len_max);
            }
            j += rows;
        }
        if (i != rows - 1) {
            mx_printchar('\n');
        }
        i++;
    }
}

void show_x_cols(t_obj **objs, int rows, int cols, int len_max) {
    int point = cols;
    int j = 0;
    int i = 0;
    int len = 0;
    
    while (i < rows) {
        while (objs[j] && j < cols) {
            mx_g_print(objs[j]);
            if ((j != cols - 1) && objs[j + 1]) {
                len = mx_strlen(objs[j]->name);
                space_print(len, len_max);
            }
            j++;
        }
        if (i != rows - 1) {
            mx_printchar('\n');
        }
        i++;
        cols += point;
    }
}

void show_objs(t_obj **objs, int len_max, int wcol, t_flags *flag) {
    int cols = (wcol / len_max) == 0 ? 1 : wcol / len_max;
    int rows = 0;
    int count = 0;
    
     while(objs[count]) {
        count++;
    }
    
    if (cols != 1 && len_max * cols > wcol) {
        cols--;
    }
    
    if (count * len_max <= cols) {
        show_g_row(objs, len_max);
    }
    else {
        rows = count / cols;
        if (count % cols != 0 || rows == 0) {
            rows++;
        }
        if (flag->x != 0) {
            show_x_cols(objs, rows, cols, len_max);
        }
        else {
            show_c_cols(objs, rows, count, len_max);
        }
    }
    mx_printchar('\n');
}

void mx_gb_output(t_obj **objs, t_flags *flag) {
    int len_max = 0;
    
    struct winsize win;
    
    if (objs) {
        len_max = len_found(objs);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        show_objs(objs, len_max, win.ws_col, flag);
    }
    else {
        return;
    }
}

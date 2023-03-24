#include "header.h"

void print_cols(t_obj **objs, int rows, int cols, int len_max) {
    int j = 0;
    int i = 0;
    int that_cols = cols;
     
    while (i < rows) {
        while (objs[j] && j < cols) {
            mx_printstr(objs[j]->name);
            if ((j != cols - 1) && objs[j + 1]) {
                mx_print_tab(mx_strlen(objs[j]->name), len_max);
            }
            j++;
        }
        if (i != rows - 1)
            mx_printchar('\n');
            
        i++; 
        cols += that_cols;
    }
}

void print(t_obj **objs, int len_max, int wincol) {
    int rows;
    int cols = 0;
    int num = 0;
    int ind = 0;
    
    if ((wincol / len_max) != 0)
        cols = wincol / len_max;
    else
        cols = 1;

    while(objs[num]) {
        num++;
    }

    if (cols != 1 && len_max * cols > wincol) {
        cols--;
    }

    if (num * len_max <= wincol) {
        while (objs[ind]) {
            mx_printstr(objs[ind]->name);
            if (objs[ind + 1]) 
                mx_print_tab(mx_strlen(objs[ind]->name), len_max);
            ind++;
        }
    }
    else {
        rows = num / cols;
        if (rows == 0 || num % cols != 0) {
            rows += 1;
        }
        print_cols(objs, rows, cols, len_max);
    }
    mx_printchar('\n');
}

void mx_x_output(t_obj **objs) {
    int len_max = 0;
    struct winsize win;
    
    if (objs) {
        len_max = len_count(objs);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        
        if (!isatty(1)) {
            print(objs, len_max, 80);
        }
        else {
            print(objs, len_max, win.ws_col);
        }
    }
    else {
        return;
    }
}

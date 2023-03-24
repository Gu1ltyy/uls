#include "header.h"

int len_count(t_obj **obj) {
    int len = 0;

    for (int i = 0; obj[i]; i++)
        if (mx_strlen(obj[i]->name) > len)
            len = mx_strlen(obj[i]->name);

    if (len % 8 != 0)
        len = 8 - (len % 8) + len;
    else
        len += 8;

    return len;
}

void mx_print_tab(int name, int len) {
    int i = 0;
    int p = len - name;;

    if (p % 8 == 0)
        i = p / 8;
    else
        i = (p / 8) + 1;

    for (int j = 0; j < i; j++)
        mx_printchar('\t');
}

void print_cols_c(t_obj **obj, int rows, int num, int len) {
    int i = 0;
    int j = 0;

    while (i < rows) {
	j = 0;
        while (i + j < num) {
            mx_printstr(obj[i + j]->name);
            if ((i + j + rows < num) && obj[i + j + 1])
                mx_print_tab(mx_strlen(obj[i + j]->name), len);
            j = j + rows;
        }
        if (i != rows - 1)
            mx_printchar('\n');
        i++;
    }
}

void print_c(t_obj **obj, int len, int wincol) {
    int rows;
    int cols = (wincol / len) != 0 ? wincol / len : 1;
    int num = 0;

    while(obj[num])
        num++;

    if (cols != 1 && len * cols > wincol)
        cols--;

    if (num * len <= wincol) {
        int i = 0;
        while (obj[i]) {
            mx_printstr(obj[i]->name);
            if (obj[i + 1]) 
                mx_print_tab(mx_strlen(obj[i]->name), len);
            i++;
        }
    }
    else {
        rows = num / cols;
        if (rows == 0 || num % cols != 0)
            rows += 1;
        print_cols_c(obj, rows, num, len);
    }
    mx_printchar('\n');
}

void mx_cb_out(t_obj **obj) {
    int len;
    struct winsize win;

    if (obj) {
        len = len_count(obj);
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        if (!isatty(1))
            print_c(obj, len, 80);
        else
            print_c(obj, len, win.ws_col);
    }
    else
        return;
}

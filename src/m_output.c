#include "header.h"

void print_m(t_obj **obj, int wincol, t_flags *flag) {
    int len = 0;
    int i = 0;

    while (obj[i]) {
        if (flag->G != 1)
            mx_printstr(obj[i]->name);
        else
            mx_g_print(obj[i]);
        
        len += mx_strlen(obj[i]->name) + 2;
        if (obj[i + 1] && len + (obj[i + 2] ? 3 : 1) + mx_strlen(obj[i + 1]->name) > wincol) {
            len = 0;
            mx_printchar('\n');
        }
        else if (obj[i + 1])
            mx_printstr(", ");
        i++;
    }
    mx_printchar('\n');
}

void mx_m_out(t_obj **obj, t_flags *flag) {
    struct winsize win;

    if (obj) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
        if (isatty(1))
            print_m(obj, win.ws_col, flag);
        else
            print_m(obj, 80, flag);
    }
    else
        return;
}

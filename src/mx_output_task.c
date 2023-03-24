#include "header.h"

void mx_frc_out(t_obj **objects, t_flags *flag) {
    int i = 0;
    while (objects[i]) {
        if (flag->G == 1) {
            mx_g_print(objects[i]);
        }
        else {
            mx_printstr(objects[i]->name);
        }
        mx_printchar('\n');
        i++;
    }
}

void mx_del_doublearr(t_obj ***files) {
    t_obj **for_del = *files;
    
    int i = 0;
    while (for_del[i] != NULL) {
        mx_strdel(&for_del[i]->name);
        mx_strdel(&for_del[i]->path);
        if (for_del[i]->open != NULL) {
            mx_del_doublearr(&for_del[i]->open);
        }
        if (for_del[i]->error) {
            mx_strdel(&for_del[i]->error);
        }
        i++;
    }
    free(*files);
    *files = NULL;
}

void mx_out_all(t_obj ***args, t_flags *flag) {
    if (!*args)
        return;
    else {
        int i = 0;

        while ((*args)[i] != NULL) {
            if (flag->files == 1) {
                if ((*args)[i]->path[0] != '/' || (*args)[i]->path[1] != '/')
                    mx_printstr((*args)[i]->path);
                else
                    mx_printstr(&(*args)[i]->path[1]);

                mx_printchar(':');
                mx_printchar('\n');
            }

            try_out_open(&(*args)[i], flag);
            if (flag->files == 1 && (*args)[i + 1])
                mx_printchar('\n');

            i++;
        }
        mx_del_doublearr(args);
    }
}

void mx_out_put_var(t_obj ***objects, t_flags *flag, int flg) {
    if (**objects == NULL) return;

    sort(&(*objects), flag);
    if (flag->l) mx_l_out(*objects, flag, flg);

    if (flag->m == 1) mx_m_out(*objects, flag);

    if (flag->C == 1 && !flag->G) mx_cb_out(*objects);
    if (flag->x == 1 && !flag->G) mx_x_output(*objects);
    if (flag->coll == 1) mx_frc_out(*objects, flag);
    if (flag->G == 1 && flag->coll != 1 && flag->m != 1 && flag->l != 1) 
        mx_gb_output(*objects, flag);

    if (!flag->G && !flag->g && !flag->o && flag->coll != 1
        && flag->m != 1 && flag->l != 1 && flag->x != 1 && flag->C != 1 
        && isatty(1)) mx_cb_out(*objects);

    if (flag->g != 1 && flag->o != 1 && flag->coll != 1
        && flag->m != 1 && flag->l != 1 && flag->x != 1 && flag->C != 1 
        && !isatty(1)) mx_frc_out(*objects, flag);
}

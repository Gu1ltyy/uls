#include "header.h"

void try_out_open(t_obj **args, t_flags *flag) {
    if ((*args)->open != NULL) {
        mx_out_put_var(&(*args)->open, flag, 1);
        if (flag->R == 1) {
            flag->files = 1;
            mx_del_files_inf(&(*args)->open, flag);
            if ((*args)->open) {
                mx_printchar('\n');
                mx_directinf(&(*args)->open, flag);
            }
        }
    }
    if ((*args)->error != NULL) {
        mx_printerr("uls: ");
        mx_printerr((*args)->path);
        mx_printerr(": ");
        mx_printerr((*args)->error);
        mx_printerr("\n");
    }
}

void mx_print_big_err(t_obj ***errs, t_flags *flag) {
    if (errs && *errs && **errs) {
        sort(errs, flag);
        flag->files = 1;
        flag->exit = 1;
  int i = 0;

        while ((*errs)[i]) {
            mx_printerr("uls: ");
            mx_printerr((*errs)[i]->name);
            mx_printerr(": ");
            mx_printerr((*errs)[i]->error);
            mx_printerr("\n");
            
            mx_strdel(&(*errs)[i]->path);
            mx_strdel(&(*errs)[i]->name);
            mx_strdel(&(*errs)[i]->error);
            free((*errs)[i]);
            (*errs)[i] = NULL;
      i++;
        }

        free(*errs);
        *errs = NULL;
    }
}



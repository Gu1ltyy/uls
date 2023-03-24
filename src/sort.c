#include "header.h"

void sort(t_obj ***disp, t_flags *flag) {
    t_obj **bond = *disp;
    t_obj *temp = NULL;
    int size = 0;
    int i = 0;
    int k;

    while (bond[size])
        size++;

    while (i < size) {
        k = i + 1;
        while (k < size) {
            if (bond[i]->error != NULL) {
                if (mx_strcmp(bond[i]->name, bond[k]->name) > 0) {
                    temp = bond[i];
                    bond[i] = bond[k];
                    bond[k] = temp;
                }
            }
            else if (flag->r ? cmp(bond[i], bond[k], flag) > 0 : cmp(bond[i], bond[k], flag) < 0) {
                temp = bond[i];
                bond[i] = bond[k];
                bond[k] = temp;
            }
            k++;
        }
        i++;
    }
}

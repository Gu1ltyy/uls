#include "header.h"

int cmp_mtime(t_obj *first, t_obj *second) {
    if (first->info.st_mtime == second->info.st_mtime) {
        return mx_strcmp(first->name, second->name);
    }
    return (first->info.st_mtime < second->info.st_mtime) ? 1 : 0;
}

int cmp_ctime(t_obj *first, t_obj *second) {
    if (first->info.st_ctime == second->info.st_ctime) {
        return mx_strcmp(first->name, second->name);
    }
    return (first->info.st_ctime < second->info.st_ctime) ? 1 : 0;
}

int cmp_atime(t_obj *first, t_obj *second) {
    if (first->info.st_atime == second->info.st_atime) {
        return mx_strcmp(first->name, second->name);
    }
    return (first->info.st_atime < second->info.st_atime) ? 1 : 0;
}

int cmp_size(t_obj *first, t_obj *second) {
    if (first->info.st_size == second->info.st_size) {
        return mx_strcmp(first->name, second->name);
    }
    return (first->info.st_size < second->info.st_size) ? 1 : 0;
}

int cmp2(t_obj *first, t_obj *second, t_flags *fl) {
    if (fl->c == 1 && fl->t == 1 && fl->S != 1) {
        return cmp_ctime(first, second);
    }
    else if (fl->t != 1 && fl->S != 1) {
        return mx_strcmp(first->name, second->name);
    }
    return cmp_mtime(first, second);
}

int cmp1(t_obj *first, t_obj *second, t_flags *fl) {
    if (fl->u == 1 && fl->t == 1 && fl->S != 1) {
        return cmp_atime(first, second);
    }
    else {
        return cmp2(first, second, fl);
    }
}

int cmp(t_obj *first, t_obj *second, t_flags *fl) {
    if (fl->S == 1) {
        return cmp_size(first, second);
    }
    else if (fl->t == 1 && fl->c != 1 && fl->u != 1) {
        return cmp_mtime(first, second);
    }
    return cmp1(first, second, fl);
}

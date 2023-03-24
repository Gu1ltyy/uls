#include "header.h"

bool file_check(t_obj **obj, t_size *size) {
    int i = 0;
    while (obj[i]) {
        if (IS_CHR(obj[i]->info.st_mode) || IS_BLK(obj[i]->info.st_mode)) {
            size->is_dev = true;
            return true;
        }
        i++;
    }

    size->is_dev = false;
    return false;
}

char *password_inf(t_obj *obj) {
    struct passwd *pw = NULL;
    char *name = NULL;

    pw = getpwuid(obj->info.st_uid);
    if (!pw)
        name = mx_itoa(obj->info.st_uid);  
    else
        name = mx_strdup(pw->pw_name); 

    return name;
}

char *group_inf(t_obj *obj) {
    struct group *grp = NULL;
    char *name = NULL;
    
    grp = getgrgid(obj->info.st_gid);
    if (!grp)
        name = mx_itoa(obj->info.st_gid);
    else
        name = mx_strdup(grp->gr_name);
    
    return name;
}

void count(t_size *size, t_obj *obj) {
    char *group_name = group_inf(obj);
    char *password_name = password_inf(obj);

    if (size->user < mx_strlen(password_name))
        size->user = mx_strlen(password_name);
    if (size->group < mx_strlen(group_name))
        size->group = mx_strlen(group_name);
    if (size->size < obj->info.st_size)
        size->size = obj->info.st_size;
    if (size->link < obj->info.st_nlink)
        size->link = obj->info.st_nlink;
    

    free(password_name);
    free(group_name);
}

void mx_l_out(t_obj **obj, t_flags *flag, int flg) {
    t_size *size = malloc(sizeof(t_size));
    size->link = 0;
    size->size = 0;
    size->group = 0;
    size->user = 0;
    int size_t = 0;
    int i = 0;

    while (obj[i]) {
        size_t += obj[i]->info.st_blocks;
        count(size, obj[i]);
        i++;
    }

    i = 0;
    if (flg == 1) {
        mx_printstr("total ");
        mx_printint(size_t);
        mx_printchar('\n');
    }

    file_check(obj, size);
    while (obj[i])
        mx_output_all(obj[i++], size, flag);

    free(size);
}

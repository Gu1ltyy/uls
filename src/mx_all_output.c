#include "header.h"

void link_out(t_obj *objects, t_size *size) {
    char *len = mx_itoa(size->link);
    char *link = mx_itoa(objects->info.st_nlink);
    int len_link = mx_strlen(link);
    int final_len = mx_strlen(len);
    int temp_len = 0;
    
    if (len_link < final_len) {
        for (temp_len = len_link; temp_len != final_len; temp_len++) {
            mx_printchar(' ');
        }
        mx_printint(objects->info.st_nlink);
    }
    else {
        mx_printint(objects->info.st_nlink);
    }
    mx_printchar(' ');
    free(link);
    free(len);
}

void group_get(int group, t_obj *objects) {
    struct group *gr = getgrgid(objects->info.st_gid);
    char *name = NULL;
    
    if (!gr) {
        name = mx_itoa(objects->info.st_gid);
    }
    else {
        name = mx_strdup(gr->gr_name);
    }
    
    int name_len = mx_strlen(name);    
    if (name_len < group) {
        mx_printstr(name);
        for (; name_len != group; name_len++) {
            mx_printchar(' ');
        }
    }
    else {
        mx_printstr(name);
    }
    
    mx_printstr("  ");
    free(name);
}

void user_get(int user, t_obj *objects) {
    struct passwd *pass = getpwuid(objects->info.st_uid);
    char *name = NULL;
    
    if (!pass) {
        name = mx_itoa(objects->info.st_uid);
    }
    else {
        name = mx_strdup(pass->pw_name);
    }
    
    int name_len = mx_strlen(name);
    if (name_len < user) {
        mx_printstr(name);
        for (; name_len != user; name_len++) {
            mx_printchar(' ');
        }
    }
    else {
        mx_printstr(name);
    }
    
    mx_printstr("  ");
    free(name);
}

void time_format(t_obj *objects, char *mtime, t_flags *flag) {
    int i = 4;

    if (flag->T != 1) {
        if (1579039200 < objects->info.st_mtime) {
            while (i < 16) {
                mx_printchar(mtime[i]);
                i++;
            }
        }
        else {
            while (i < 10) {
                mx_printchar(mtime[i]);
                i++;
            }
            mx_printstr("  ");
            i = 20;
            while (i < 24) {
                mx_printchar(mtime[i]);
                i++;
            }
        }
    }
    else {
        while (i < mtime[i]) {
            mx_printchar(mtime[i]);
            i++;
        }
    }
    mx_printstr(" ");
}

void sublink_out(t_obj *objects) {
    ssize_t b_size = 0;
    if (objects->info.st_size == 0)
         b_size = 100;
     else
         b_size = objects->info.st_size + 1;
    char *buff = mx_strnew(b_size);
    ssize_t numb_ch = readlink(objects->path, buff, b_size);
    
    mx_printstr(" -> ");
    if (numb_ch >= 0) {
        mx_printstr(buff);
    }
    mx_strdel(&buff);
}

void form_visual_output(t_flags *flag, t_obj *objects) {
    if (IS_LNK(objects->info.st_mode)) {
        mx_printstr(objects->name);
        sublink_out(objects);
    }
    else if (flag->G == 1) {
        mx_g_print(objects);
    }
    else {
        mx_printstr(objects->name);
    }
}

void mx_output_all(t_obj *objects, t_size *size, t_flags *flag) {
    time_t *atime = &objects->info.st_atime;
    time_t *mtime;
    time_t *c_time = &objects->info.st_ctime;
    
    print_arg(objects);
    link_out(objects, size);
    
    if (flag->g == 0) {
        if(flag->o == 1 || flag->l == 1) {
            user_get(size->user, objects);
        }
    }
    
    if (flag->o == 0) {
        if(flag->g == 1 || flag->l == 1) {
            group_get(size->group, objects);
        }
    }

    mx_size_show(size, objects);
    
    if (flag->c == 1) {
        mtime = c_time;
    }
    else if (flag->u == 1) {
        mtime = atime;
    }
    else {
        mtime = &objects->info.st_mtime;
    }
    
    time_format(objects, ctime(mtime), flag);
    form_visual_output(flag, objects);
    mx_printchar('\n');
}


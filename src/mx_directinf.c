#include "header.h"

int check_hid(char *name, t_flags *flag) {
    if (mx_strcmp(name, ".") == 0 || mx_strcmp(name, "..") == 0
    || flag->A != 1) {
        return 0;
    }
    return 1;
}

int get_nbr(t_obj **args, t_flags *flag) {
    int numbr = 0;
    DIR *point_dir = opendir((*args)->path);
    struct dirent *dirct_s;

    if (IS_DIR((*args)->info.st_mode) || IS_LNK((*args)->info.st_mode)) {
        if (!point_dir) {
            (*args)->error = mx_strdup(strerror(errno));
            flag->exit = 1;
            return 1;
        }

        while ((dirct_s = readdir(point_dir))) {
            if (dirct_s->d_name[0] != '.' || check_hid(dirct_s->d_name, flag)) {
                numbr++;
            }
        }

        closedir(point_dir);
    }

    return numbr;
}

t_obj *new_obj_create(char *name, char *path) {
    t_obj *new_obj =(t_obj *)malloc(1 * sizeof(t_obj));
    new_obj->error = NULL;
    new_obj->open = NULL;
    
    new_obj->path = mx_strdup(path);
    new_obj->name = mx_strdup(name);
    
    mx_join(&new_obj->path, "/");
    mx_join(&new_obj->path, name);
    
    if (lstat(new_obj->path, &(new_obj->info)) == -1) {
        new_obj->error = mx_strdup(strerror(errno));
    }
    return new_obj;
}

void directory_opn(t_obj ***args, t_flags *flag) {
    DIR *point_dir;
    struct dirent *dirct_s;
    int number = 0;
    int i = 0;
    
    while ((*args)[i] != NULL) {
        number = get_nbr(&(*args)[i], flag);
        if (number > 0) {
             (*args)[i]->open = malloc((number + 1) * sizeof(t_obj*));
             if ((point_dir = opendir((*args)[i]->path)) != NULL) {
             	 number = 0;
             	 dirct_s = readdir(point_dir); 
                 while (dirct_s != NULL) {
                     if (dirct_s->d_name[0] != '.'
                     || check_hid(dirct_s->d_name, flag) == 1) {
                         (*args)[i]->open[number++] = new_obj_create(dirct_s->d_name, (*args)[i]->path);
                     }
                     dirct_s = readdir(point_dir);
                 }
                 (*args)[i]->open[number] = NULL;
                 closedir(point_dir);
             }
        }
        i++;
    }
    mx_out_all(args, flag);
}

void mx_directinf(t_obj ***args, t_flags *flag) {
    t_obj **objects = mx_fileobj(&(*args), flag);
    
    if (objects) {
        mx_out_put_var(&objects, flag, 0);
        
        if (*args) {
            mx_printchar('\n');
        }
        flag->files = 1;
        mx_del_doublearr(&objects);
    }
    
    if (*args) {
        directory_opn(&(*args), flag);
    }
}

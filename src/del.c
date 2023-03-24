#include "header.h"

void mx_objs_del(t_obj ***args, t_obj **dir) {
    t_obj **del_arr = *args;
    int i = 0; 

    while (del_arr[i]!= NULL) {
        if (del_arr[i]->error)
            mx_strdel(&del_arr[i]->error);
            
        mx_strdel(&del_arr[i]->path);
        mx_strdel(&del_arr[i]->name);

        free(del_arr[i]);
        del_arr[i] = NULL;
        
        i++;
    }

    free(*args);
    *args = dir;
}

t_obj *create_node(t_obj *args) {
    t_obj *node = (t_obj *)malloc(1 * sizeof(t_obj));
    node->path = mx_strdup(args->path);
    node->name = mx_strdup(args->name);

    if (args->error == NULL)
        node->error = NULL;
    else {
        node->error = NULL;
        node->error = mx_strdup(args->error);
    }
    lstat(node->path, &(node->info));
    if (args->open == NULL)
        node->open = NULL;
    else 
        node->open = args->open;

    return node;
}

void create_mem(t_obj ***dir, t_obj ***args) {
    int n = 0;
    int i = 0;

    while ((*args)[i] != NULL) {
        if ((*args)[i]->error == NULL && IS_DIR((*args)[i]->info.st_mode) &&
            mx_strcmp((*args)[i]->name, ".") != 0 && mx_strcmp((*args)[i]->name, "..") != 0) {
            n++;
        }
	i++;
    }

    if (n > 0)
        *dir = malloc((n + 1) * sizeof(t_obj *));
}

void mx_del_files_inf(t_obj ***args, t_flags *flag) {
    t_obj **dir = NULL;
    int num = 0;
    int i = 0;

    create_mem(&dir, args);
    while ((*args)[i] != NULL) {
        if ((*args)[i]->error == NULL && IS_DIR((*args)[i]->info.st_mode) &&
            mx_strcmp((*args)[i]->name, ".") != 0 && mx_strcmp((*args)[i]->name, "..") != 0) {
            dir[num] = create_node((*args)[i]);
            num++;
            dir[num] = NULL;
        }
	i++;
    }

    flag->files = 1;
    mx_objs_del(args, dir);
}

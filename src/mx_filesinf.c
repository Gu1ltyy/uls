 #include "header.h"

t_numbr *new_numbr() {
    t_numbr *numbr = malloc(sizeof(t_numbr));
    
    numbr->dircts_num = 0;
    numbr->files_num = 0;
    numbr->errs_num = 0;
    numbr->count = 0;
    return numbr;
}

t_obj *new_objs(t_obj *args) {
    t_obj *obj = (t_obj *)malloc(1 * sizeof(t_obj));
    
    obj->path = mx_strdup(args->path);
    obj->name = mx_strdup(args->name);
    
    if (!args->error) {
        obj->error = NULL;
    }
    else {
        obj->error = mx_strdup(args->error);
    }
    lstat(obj->path, &(obj->info));
    
    if (args->open == NULL) {
        obj->open = NULL;
    }
    else {
        obj->open = args->open;
    }
    
    return obj;
}

void count_for_mem(t_obj ***files, t_obj ***dircts, t_obj ***errs, t_obj ***args) {
    int dir_num = 0;
    int file_num = 0;
    int err_num = 0;
    
    int i = 0;
    while ((*args)[i] != NULL) {
        if ((*args)[i]->error == NULL) {
            if (IS_DIR((*args)[i]->info.st_mode)) {
                dir_num++;
            }
            else {
                file_num++;
            }
        }
        else {
            err_num++;
        }
        
        i++;
    }
    if (dir_num > 0) {
        *dircts = malloc((dir_num + 1) * sizeof(t_obj *));
    }
    if (file_num > 0) {
        *files = malloc((file_num + 1) * sizeof(t_obj *));
    }
    if (err_num > 0) {
        *errs = malloc((err_num + 1) * sizeof(t_obj *));
    }
}

void file_dirct_objs(t_obj **args, t_numbr *numbr, t_obj ***files, t_obj ***dircts) {
    if (IS_DIR((*args)->info.st_mode)) {
        (*dircts)[numbr->dircts_num] = new_objs((*args));
        numbr->dircts_num++;
        (*dircts)[numbr->dircts_num] = NULL;
    }
    else {
        (*files)[numbr->files_num] = new_objs((*args));
        numbr->files_num++;
        (*files)[numbr->files_num] = NULL;
    }
}

t_obj **mx_fileobj(t_obj ***args, t_flags *flag) {
    t_numbr *numbs = new_numbr();
    t_obj **dircts = NULL;
    t_obj **files = NULL;
    t_obj **errs = NULL;
    
    count_for_mem(&files, &dircts, &errs, args);
    
    while ((*args)[numbs->count] != NULL) {
        if ((*args)[numbs->count]->error != NULL) {
            errs[numbs->errs_num++] = new_objs((*args)[numbs->count]);
            errs[numbs->errs_num] = NULL;
        }
        else {
            file_dirct_objs(&(*args)[numbs->count], numbs, &files, &dircts);
        }
        
        numbs->count++;
    }
    
    if (numbs->dircts_num > 1) {
        flag->files = 1;
    }
    
    mx_objs_del(args, dircts);
    mx_print_big_err(&errs, flag);
    free(numbs);
    
    return files;
}

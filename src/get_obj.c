#include "header.h"

t_obj *create_obj_node(char *file) {
    t_obj *node = (t_obj *)malloc(1 * sizeof(t_obj));
    node->open = NULL;
    node->error = NULL;
    
    node->path = mx_strdup(file);
    node->name = mx_strdup(file);

    if (lstat(file, &(node->info)) == -1)
        node->error = mx_strdup(strerror(errno));

    return node;
}

t_obj **create_obj_list(char **name, int i) {
    int counter = 0;
    t_obj **list = malloc(i * sizeof(t_obj *));

    while (name[counter]) {
        list[counter] = create_obj_node(name[counter]);
        counter++;
    }
    list[counter] = NULL;

    return list;
}

char **get_names(int argc, char **argv, int counter, int *i) {
    char **name = NULL;
    int j = counter;
    
    if (counter == argc) {
        name = malloc(2 * sizeof(char *));
        name[0] = mx_strdup(".");
        name[1] = NULL;
        *i = 2;
    }
    else {
        while (argv[j])
            j++;

        name = malloc((j - counter + 1) * sizeof(char *));
        j = 0;
        while (argv[counter]) {
            name[j] = mx_strdup(argv[counter]);
            j++;
            counter++;
        }

        *i = j + 1;
        name[j] = NULL;
    }

    return name;
}

t_obj **get_obj(int argc, char **argv, int counter) {
    int i = 0;
    char **names = get_names(argc, argv, counter, &i);
    t_obj **args = create_obj_list(names, i);

    mx_del_strarr(&names);
    
    return args;
}

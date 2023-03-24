#include "header.h"

void add_flags_pt4(t_flags **flags, char fl) {
    mx_printerr("uls: illegal option -- ");
    write(2, &fl, 1);
    mx_printerr("\n");
    mx_printerr("usage: uls [-ACGRSTcglmortux1] [file ...]\n");
    free(*flags);
    flags = NULL;
    exit(1);
}

void add_flags_pt3(t_flags **flags, char fl) {
    (*flags)->l = 0;
    (*flags)->C = 0;
    (*flags)->coll = 0;
    (*flags)->x = 0;
    (*flags)->m = 0;

    switch (fl) {
        case 'l':
            (*flags)->l = 1;
            break;
        case 'C':
            (*flags)->C = 1;
            break;
        case '1':
            (*flags)->coll = 1;
            break;
        case 'x':
            (*flags)->x = 1;
            break;
        case 'm':
            (*flags)->m = 1;
            break;
        default:
            add_flags_pt4(flags, fl);
    }
}

void add_flags_pt2(t_flags **flags, char fl) {
    switch (fl) {
        case 'S':
            (*flags)->S = 1;
            break;
        case 'r': 
            if ((*flags)->r != -1)
                (*flags)->r = 0;
	    break;
        case 'G':
            if (!isatty(1))
                (*flags)->G = 0;
	    break;
        case 'R':
            (*flags)->R = 1;
            break;
        case 'A':
            (*flags)->A = 1;
            break;
        case 'g':
            (*flags)->g = 1;
            (*flags)->l = 1;
            break;
        case 'o':
            (*flags)->o = 1;
            (*flags)->l = 1;
            break;
        default:
            add_flags_pt3(flags, fl);
    }
}

void add_flags_pt1(t_flags **flags, char fl) {
    switch (fl) {
        case 'T':
            (*flags)->T = 1;
            break;
        case 'G':
            if (isatty(1))
                (*flags)->G = 1;
	    break;
        case 'c':
            (*flags)->c = 1; 
            (*flags)->u = 0;
            break;
        case 't':
            (*flags)->t = 1;
            break;
        case 'u':
            (*flags)->u = 1;
            (*flags)->c = 0;
            break;
        default:
            add_flags_pt2(flags, fl);
    }
}

void null_flags(t_flags **flags) {
    (*flags)->l = 0;
    (*flags)->R = 0;
    (*flags)->a = 0;
    (*flags)->A = 0;
    (*flags)->G = 0;
    (*flags)->T = 0;
    (*flags)->C = 0;
    (*flags)->x = 0;
    (*flags)->t = 0;
    (*flags)->u = 0;
    (*flags)->c = 0;
    (*flags)->S = 0;
    (*flags)->coll = 0;
    (*flags)->m = 0;
    (*flags)->g = 0;
    (*flags)->o = 0;
    (*flags)->r = 1;
}

t_flags *get_flags(char *argv[], int *counter) {
    t_flags *flags = malloc(sizeof(t_flags));
    int j = 1;

    null_flags(&flags);

    while (argv[*counter] && argv[*counter][0] == '-') {
        if (argv[*counter][1] == '-')
            break;
        j = 1;
        while (argv[*counter][j])
            add_flags_pt1(&flags, argv[*counter][j++]);
        if (argv[*counter][1] == '\0')
            break;
    (*counter)++;
}

    return flags;
} 

int main(int argc, char *argv[]) {
    int count = 1;
    int ex = 0;
    t_flags *flags = get_flags(argv, &count);
    t_obj **args = get_obj(argc, argv, count);

   if (args)
        mx_directinf(&args, flags);
    if (flags->exit == 1)
        ex = 1;

    free(flags);
    flags = NULL;

    exit(ex);
}

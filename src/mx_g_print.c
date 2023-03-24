#include "header.h"

void mx_g_print(t_obj *objs) {
    if (IS_DIR(objs->info.st_mode)) {
        mx_printstr("\033[34m");
    }
    else if (IS_LNK(objs->info.st_mode)) {
        mx_printstr("\033[35m");
    }
    else if (objs->info.st_mode & S_IXOTH) {
        mx_printstr(LS_COLOR_RED);
    }
    else if (IS_SOCK(objs->info.st_mode)) {
        mx_printstr("\033[32m");
    }
    else if (IS_CHR(objs->info.st_mode)) {
        mx_printstr("\033[34;43m");
    }
    else if (IS_BLK(objs->info.st_mode)) {
        mx_printstr("\033[34;46m");
    }
    else if (IS_EXEC(objs->info.st_mode)) {
        mx_printstr("\033[31m");
    }
    else if (IS_FIFO(objs->info.st_mode)) {
        mx_printstr("\033[33m");
    }
    else if (IS_WHT(objs->info.st_mode)) {
        mx_printstr("\033[36m");
    }
    mx_printstr(objs->name);
    mx_printstr(LS_COLOR_RESET);
}

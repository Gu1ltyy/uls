#include "header.h"

char check_acl(t_obj *print) {
    acl_t temp;

    if ((temp = acl_get_file(print->path, ACL_TYPE_EXTENDED))) {
        acl_free(temp);
        return ('+');
    }

    if (listxattr(print->path, NULL, 0, XATTR_NOFOLLOW) > 0)
        return ('@');

    return (' ');
}

char check_type(t_obj *print) {
    return IS_WHT(print->info.st_mode) ? 'w'
         : IS_DIR(print->info.st_mode) ? 'd'
         : IS_FIFO(print->info.st_mode) ? 'p'
         : IS_BLK(print->info.st_mode) ? 'b'
         : IS_LNK(print->info.st_mode) ? 'l'
         : IS_CHR(print->info.st_mode) ? 'c'
         : IS_SOCK(print->info.st_mode) ? 's'
         : '-';
}

void print_arg(t_obj *print) {
    char chmod[12];
    int i = 0;
    
    chmod[i++] = check_type(print);
    chmod[i++] = (S_IRUSR & print->info.st_mode) ? 'r' : '-';
    chmod[i++] = (S_IWUSR & print->info.st_mode) ? 'w' : '-';
    chmod[i++] = (S_IXUSR & print->info.st_mode) ? 'x' : '-';
    chmod[i++] = (S_IRGRP & print->info.st_mode) ? 'r' : '-';
    chmod[i++] = (S_IWGRP & print->info.st_mode) ? 'w' : '-';
    chmod[i++] = (S_IXGRP & print->info.st_mode) ? 'x' : '-';
    chmod[i++] = (S_IROTH & print->info.st_mode) ? 'r' : '-';
    chmod[i++] = (S_IWOTH & print->info.st_mode) ? 'w' : '-';
    chmod[i++] = (S_IXOTH & print->info.st_mode) ? 'x' : '-';
    chmod[i++] = check_acl(print);
    chmod[i++] = '\0';
    if (S_ISUID & print->info.st_mode)
        chmod[3] == '-' ? chmod[3] = 'S' : chmod[3] == 's';

    if (S_ISGID & print->info.st_mode) 
        chmod[6] == '-' ? chmod[6] = 'S' : chmod[6] == 's';

    if (S_ISVTX & print->info.st_mode)
        chmod[9] == '-' ? chmod[9] = 'T' : chmod[9] == 't';

    for (int j = 0; chmod[j]; j++)
        mx_printchar(chmod[j]);

    mx_printchar(' ');
}

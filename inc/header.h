#ifndef HEADER_H
#define HEADER_H

#include "libmx.h"
#include "dirent.h"
#include "time.h"
#include "sys/stat.h"
#include "sys/types.h"
#include "sys/xattr.h"
#include "sys/acl.h"
#include "sys/ioctl.h"
#include "pwd.h"
#include "grp.h"
#include "errno.h"
#include "dirent.h"
#include "string.h"

#define IS_SOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#define IS_FIFO(mode) (((mode) & S_IFMT) == S_IFIFO)
#define IS_WHT(mode) (((mode) & S_IFMT) == S_IFWHT)
#define IS_REG(mode) (((mode) & S_IFMT) == S_IFREG)
#define IS_EXEC(mode) ((mode) & S_IXUSR)
#define IS_BLK(mode) (((mode) & S_IFMT) == S_IFBLK)
#define IS_CHR(mode) (((mode) & S_IFMT) == S_IFCHR)
#define IS_LNK(mode) (((mode) & S_IFMT) == S_IFLNK)
#define IS_DIR(mode) (((mode) & S_IFMT) == S_IFDIR)

#define LS_COLOR_RED        "\x1b[31m"
#define LS_COLOR_RESET      "\x1b[0m"

typedef struct s_flags t_flags;
typedef struct s_obj t_obj;
typedef struct s_numbr_inf t_numbr;
typedef struct s_size t_size;

struct s_flags {
    int l;
    int R;
    int a;
    int A;
    int G;
    int T;
    int C;
    int x;
    int r;
    int t;
    int u;
    int c;
    int S;
    int coll;
    int m;
    int files;
    int g;
    int o;
    int exit;
};

struct s_obj {
    char *name;
    char *path;
    char *error;
    struct stat info;
    struct s_obj **open;
};

struct s_numbr_inf {
    int dircts_num;
    int files_num;
    int errs_num;
    int count;
};

struct s_size {
    bool is_dev;
    int group;
    int user;
    int link;
    int size;
};

void mx_del_doublearr(t_obj ***files);
void mx_join(char **res, char *s2);
void mx_print_tab(int name, int len);
void mx_l_out(t_obj **obj, t_flags *flag, int flg);
void mx_x_output(t_obj **objs);
void mx_m_out(t_obj **obj, t_flags *flag);
void mx_gb_output(t_obj **objs, t_flags *flag);
void mx_g_print(t_obj *objs);
void mx_cb_out(t_obj **obj);
void mx_out_all(t_obj ***args, t_flags *flag);
void print_arg(t_obj *print);
void sort(t_obj ***disp, t_flags *flag);
void mx_size_show(t_size *size, t_obj *objects);
void mx_output_all(t_obj *objects, t_size *size, t_flags *flag);

t_obj **get_obj(int argc, char **argv, int counter);
t_obj **mx_fileobj(t_obj ***args, t_flags *flag);
int len_count(t_obj **obj);
void mx_objs_del(t_obj ***args, t_obj **dir);
void mx_del_files_inf(t_obj ***args, t_flags *flag);
void mx_out_put_var(t_obj ***objects, t_flags *flag, int flg);
void try_out_open(t_obj **args, t_flags *flag);
void mx_directinf(t_obj ***args, t_flags *flag);
void mx_print_big_err(t_obj ***errs, t_flags *flag);

int cmp_mtime(t_obj *first, t_obj *second);
int cmp_ctime(t_obj *first, t_obj *second);
int cmp_atime(t_obj *first, t_obj *second);
int cmp_size(t_obj *first, t_obj *second);
int cmp2(t_obj *first, t_obj *second, t_flags *fl);
int cmp1(t_obj *first, t_obj *second, t_flags *fl);
int cmp(t_obj *first, t_obj *second, t_flags *fl);

#endif

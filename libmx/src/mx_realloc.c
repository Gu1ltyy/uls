#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (!ptr)
        return malloc(size);
    
    size_t length = malloc_size(ptr); //malloc_usable_size for linux; malloc_size for macos
    void *new_ptr = NULL;

    if (size <= length)
        return ptr;

    new_ptr = malloc(size);
    mx_memcpy(new_ptr, ptr, length);
    free(ptr);
    return new_ptr;
}


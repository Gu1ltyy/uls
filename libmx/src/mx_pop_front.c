#include "libmx.h"

void mx_pop_front(t_list **head) {
    if (head == NULL || (*head) == NULL)
        return;
    
    if ((*head) -> next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    t_list *temp = (*head) -> next;
    if (!temp)
        return;
    
    free(*head);
    *head = temp;
}


#ifndef LIST_RC86CSMV

#define LIST_RC86CSMV

/* A singly linked list */

struct list
{
    void *data;
    struct list *next;
};

typedef struct list* list_t;

list_t list_new(void *data);

list_t list_push_front(list_t list, void *data);
list_t list_pop_front(list_t list);

list_t list_push_tail(list_t list, void *data);
list_t list_pop_tail(list_t list);

void *list_get_front(list_t list);
void *list_get_tail(list_t list);

size_t list_size(list_t list);

#endif /* end of include guard: LIST_RC86CSMV */

#include <stdlib.h>
#include "list.h"

list_t list_new(void *data)
{
    list_t list = malloc(sizeof(struct list));
    if(list == NULL)
	return NULL;
    list->data = data;
    list->next = NULL;
    return list;
}

list_t list_push_front(list_t list, void *data)
{
    list_t new = list_new(data);
    if(list != NULL)
	new->next = list;
    return new;
}

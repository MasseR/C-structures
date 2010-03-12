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

list_t list_push_tail(list_t list, void *data)
{
    list_t iterator;
    list_t new = list_new(data);
    if(list == NULL)
	return new;
    for(iterator = list; iterator->next != NULL; iterator = iterator->next)
    {}
    iterator->next = new;
    return list;
}

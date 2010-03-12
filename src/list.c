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

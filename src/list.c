#include <stdlib.h>
#include <assert.h>
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

void *list_get_front(list_t list)
{
    assert(list != NULL);
    return list->data;
}

void *list_get_tail(list_t list)
{
    assert(list != NULL);
    list_t iterator;
    for(iterator = list; iterator->next != NULL;
	   iterator = iterator->next)
    {}
    return iterator->data;
}

list_t list_pop_front(list_t list)
{
    list_t next = list->next;
    free(list);
    return next;
}

list_t list_pop_tail(list_t list)
{
    assert(list != NULL);
    list_t iterator;
    list_t previous;
    if(list->next == NULL)
    {
	free(list);
	return NULL;
    }
    else
    {
	for(iterator = list;
		iterator->next != NULL;
		previous = iterator, iterator = iterator->next)
	{
	}
	free(iterator);
	previous->next = NULL;
    }
    return list;
}

size_t list_size(list_t list)
{
    size_t size = 0;
    list_t iterator;
    if(list == NULL)
	return 0;
    for(iterator = list;
	    iterator != NULL;
	    iterator = iterator->next)
	size++;
    return size;
}

void list_foreach(list_t list, func_t func)
{
    assert(list != NULL);
    list_t iter;
    if(func == NULL)
	return;
    for(iter = list; iter != NULL; iter = iter->next)
	func(iter->data);
}

list_t list_free(list_t list, func_t func)
{
    list_t iterator = NULL, previous = NULL;
    list_foreach(list, func);
    for(iterator = list; iterator != NULL; previous = iterator, iterator = iterator->next)
	free(previous);
    free(previous);
    return NULL;
}

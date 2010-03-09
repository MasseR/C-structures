#include "heap.h"
#define HEAP_SIZE sizeof(struct heap)

heap_t heap_new(size_t size)
{
    int i;
    heap_t heap = NULL;
    heap = malloc(HEAP_SIZE);
    if(heap == NULL)
	return NULL;
    heap->size = size;
    heap->tree = malloc(size * sizeof(void*));
    for(i = 0; i < size; i++)
	heap->tree[i] = NULL;
    return heap;
}

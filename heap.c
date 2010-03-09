#include <assert.h>
#include "heap.h"

#define HEAP_SIZE sizeof(struct heap)
#define LEFT(k) (2*(k))
#define RIGHT(k) LEFT(k)+1

heap_t heap_new(size_t size, cmp_t cmp)
{
    int i;
    heap_t heap = NULL;
    heap = malloc(HEAP_SIZE);
    if(heap == NULL)
	return NULL;
    heap->size = size;
    heap->cmp = cmp;
    heap->tree = malloc(size * sizeof(void*));
    for(i = 0; i < size; i++)
	heap->tree[i] = NULL;
    return heap;
}

heap_t heap_insert(heap_t heap, void *node)
{
    assert(heap != NULL);
    heap->tree[0] = node;

    return heap;
}

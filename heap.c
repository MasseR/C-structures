#include <assert.h>
#include "heap.h"

#define HEAP_SIZE sizeof(struct heap)
#define LEFT(k) (2*((k)+1))-1
#define RIGHT(k) LEFT(k)+1
#define PARENT(k) (((k)+1)>>1)-1

static heap_t swap(heap_t heap, int k, int l)
{
    void *temp = heap->tree[k];
    heap->tree[k] = heap->tree[l];
    heap->tree[l] = temp;

    return heap;
}

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
    int i = 0;

    /* Find the first NULL */
    for(i = 0; heap->tree[i] != NULL; i++)
    {}
    heap->tree[i] = node;
    while(i > 0 && heap->cmp(heap->tree[i], heap->tree[PARENT(i)]))
    {
	swap(heap, i, PARENT(i));
	i = PARENT(i);
    }

    return heap;
}

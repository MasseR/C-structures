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

heap_t heap_remove(heap_t heap)
{
    assert(heap != NULL);
    int i;

    /* Traverse the index to the last position */
    for(i = 0; heap->tree[++i] != NULL;)
    {}
    i-=1;

    heap->tree[0] = NULL;

    /* The rightmost leaf as the first */
    if(i > 0)
    {
	swap(heap, 0, i);
    }
    if(i < 2) /* After swapping, the heap has only the root node */
	return heap;

    i = 0;

    if(!heap->cmp(heap->tree[i], heap->tree[LEFT(i)]))
    {
	if(!heap->cmp(heap->tree[i], heap->tree[RIGHT(i)]))
	{
	    /* Choose the child to be swapped with */
	    int swp = heap->cmp(heap->tree[LEFT(i)],
		    heap->tree[RIGHT(i)]) ? LEFT(i) : RIGHT(i);
	    swap(heap, i, swp);
	}
	else
	{
	    swap(heap, i, LEFT(i));
	}
    }

    return heap;
}

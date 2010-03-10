/*
 Copyright (c) 2010 Mats Rauhala

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
*/
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

static heap_t downheap(heap_t heap)
{
    int i = 0;
    while(LEFT(i) < heap->size && heap->tree[LEFT(i)] != NULL)
    {
	if(!heap->cmp(heap->tree[i], heap->tree[LEFT(i)]))
	{
	    if(heap->tree[RIGHT(i)] != NULL && !heap->cmp(heap->tree[i], heap->tree[RIGHT(i)]))
	    {
		/* Choose the child to be swapped with */
		int swp = heap->cmp(heap->tree[LEFT(i)],
			heap->tree[RIGHT(i)]) ? LEFT(i) : RIGHT(i);
		swap(heap, i, swp);
		i = swp;
	    }
	    else
	    {
		swap(heap, i, LEFT(i));
		i = LEFT(i);
	    }
	}
	else if(heap->tree[RIGHT(i)] != NULL && !heap->cmp(heap->tree[i], heap->tree[RIGHT(i)]))
	{
	    swap(heap, i, RIGHT(i));
	}
	else
	    break;
    }
    return heap;
}

heap_t heap_new(size_t size, cmp_t cmp)
{
    assert(cmp != NULL);
    int i;
    heap_t heap = NULL;
    heap = malloc(HEAP_SIZE);
    if(heap == NULL)
	return NULL;
    heap->size = size;
    heap->nodes = 0;
    heap->cmp = cmp;
    heap->exfunc = NULL;
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

    heap->nodes++;

    return heap;
}

heap_t heap_remove(heap_t heap)
{
    assert(heap != NULL);
    int i;

    heap->nodes--;

    if(heap->exfunc != NULL)
	heap->exfunc(heap->tree[0]);

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

    downheap(heap);

    return heap;
}

void *heap_peek(heap_t heap)
{
    assert(heap != NULL);
    return heap->tree[0];
}

heap_t heap_set_on_exit(heap_t heap, exit_func e)
{
    heap->exfunc = e;
    return heap;
}

void heap_free(heap_t heap)
{
    int i;
    for(i = 0; i < heap->size && heap->tree[i] != NULL; i++)
    {
	if(heap->exfunc != NULL)
	    heap->exfunc(heap->tree[i]);
    }

    free(heap);
}

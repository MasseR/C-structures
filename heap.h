#ifndef HEAP_6HM1TBFB

#define HEAP_6HM1TBFB

#include <stdlib.h>

typedef int (*cmp_t)(void *, void *);

struct heap
{
    size_t size;
    void **tree;
    cmp_t cmp;
};

typedef struct heap* heap_t;


heap_t heap_new(size_t size, cmp_t cmp);

heap_t heap_insert(heap_t heap, void *node);

heap_t heap_remove(heap_t heap);

#endif /* end of include guard: HEAP_6HM1TBFB */


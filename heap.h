#ifndef HEAP_6HM1TBFB

#define HEAP_6HM1TBFB

#include <stdlib.h>

struct heap
{
    size_t size;
    void **tree;
};
typedef struct heap* heap_t;
heap_t heap_new(size_t size);

#endif /* end of include guard: HEAP_6HM1TBFB */


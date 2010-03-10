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
#ifndef HEAP_6HM1TBFB

#define HEAP_6HM1TBFB

#include <stdlib.h>

typedef int (*cmp_t)(void *, void *);
typedef void (*exit_func)(void *);

struct heap
{
    size_t size;
    size_t nodes;
    void **tree;
    cmp_t cmp;
    exit_func exfunc;
};

typedef struct heap* heap_t;


heap_t heap_new(size_t size, cmp_t cmp);

heap_t heap_insert(heap_t heap, void *node);

heap_t heap_remove(heap_t heap);

heap_t heap_set_on_exit(heap_t heap, exit_func e);

void *heap_peek(heap_t heap);

void heap_free(heap_t heap);

#endif /* end of include guard: HEAP_6HM1TBFB */


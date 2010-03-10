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
/* @file heap.h Heap implementation
 * @author Mats Rauhala
 * @date 10.03.2010
 * */
#ifndef HEAP_6HM1TBFB

#define HEAP_6HM1TBFB

#include <stdlib.h>

/* @brief The root node
 *
 * Returns the root node of the heap
 *
 * @arg heap The wanted heap
 * @return Root node
 */
#define heap_peek(heap) (heap)->tree[0]

/* @brief Typedef for comparison function */
typedef int (*cmp_t)(void *, void *);
/* @brief Typedef for exit function
 *
 * This is a typedef to a function that is called every time when a node needs
 * to be deleted, no matter whether it's from explicit heap_remove() or
 * implicit heap_free() */
typedef void (*exit_func)(void *);

/* @brief The heap structure
 *
 * Users shouldn't need to care about this one as it is only used internally.
 * Nearly all heap functions return an instance of this.
 */
struct heap
{
    size_t size;
    size_t nodes;
    void **tree;
    cmp_t cmp;
    exit_func exfunc;
};

typedef struct heap* heap_t;


/* @brief Create a new heap
 *
 * Creates a new heap structure. Every node is filled with NULL.
 *
 * @arg size Node size. The heap is kept in an array, and no automatic resizing is done
 * @arg cmp Compare function. Can't be NULL
 * @return Instance to the new heap
 */
heap_t heap_new(size_t size, cmp_t cmp);

/* @brief Insert a new node
 *
 * Inserts a new node to the heap. The heap returned is exactly the same as the
 * on given as arguments
 *
 * @arg heap Heap allocated with heap_new()
 * @arg node The node to be inserted. Should not be null
 * @return Heap
 */
heap_t heap_insert(heap_t heap, void *node);

/* @brief Remove the root node
 *
 * Remove the root node and perform downheap to create a proper heap again.
 * @arg heap The heap from which to remove the root node
 * @return Heap
 */
heap_t heap_remove(heap_t heap);

/* @brief Set the on_exit function
 *
 * The exit_func function is called anytime when a node is removed. 
 * For example heap_set_on_exit(heap, &free);
 *
 * @arg heap The heap to be modified
 * @e The exit function
 * @return Heap
 */
heap_t heap_set_on_exit(heap_t heap, exit_func e);

/* @brief Free the heap
 *
 * Calls the on_exit function on all non-null nodes and then free()'s itself
 *
 * @arg heap The heap to free
 */
void heap_free(heap_t heap);

void heap_sort(void **array, size_t size, cmp_t cmp);

#endif /* end of include guard: HEAP_6HM1TBFB */


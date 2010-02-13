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

/* @file stack.h Stack implementation
 * @author Mats Rauhala
 * @date 12.02.2010
 *
 * Usage example:
 *
 * stack *s = stack_push("world", NULL);
 * s = stack_push("hello", s);
 * do {
 *  printf("%s\n", (char*)stack_get(s));
 * } while((s = stack_pop) != NULL)
 */
#ifndef STACK_H

#define STACK_H
#include <stdlib.h>

struct stack_t {
    void *data;
    struct stack_t *next;
};
typedef struct stack_t stack;

/* @brief Allocate space for a new stack item.
 *
 * Allocate space for a new stack item and fill with NULL data. Users should
 * not be required to use this function directly, instead @see stack_new which
 * allocates space for new items. */
inline stack* stack_new(void)
{
    stack *s = malloc(sizeof(stack));
    s->data = NULL;
    s->next = NULL;
    return s;
}

/* @brief Push new data to the stack
 *
 * Push new data to the stack structure. If parameter old is NULL, new space is
 * allocated for the first item. This is the recommended way to init a new
 * stack structure.
 *
 * With both parameters set, the first item is replaced with new data, and the
 * previous first, is set to the next.
 *
 * @param data A void pointer for data. Nothing is done when freeing with pop
 * @param old The existing stack structure or new in case a new stack is to be
 * created
 *
 * @return The first stack item
 */
inline stack* stack_push(void *data, stack* old)
{
    stack *s = stack_new();
    s->data = data;
    s->next = old;
    return s;
}

/* @brief Remove the first entry
 *
 * Pops (removes) the first entry and also returns the next entry. The first
 * entry is freed, but nothing is done separately for the data, which means
 * that if the data has been malloc'd, it needs to be freed separately.
 *
 * @param old The first stack item
 * 
 * @return The next stack item
 */
inline stack* stack_pop(stack* old)
{
    if(old == NULL) return NULL;
    stack *s = old->next;
    free(old);
    return s;
}

/* @brief Return true if the element is found
 *
 * Try to find a specified element. Return true if the element is in
 * stack, otherwise return false
 */
inline int stack_search(stack *head, int cmp(void *a, void *b), void *search)
{
    stack *iterator = head;
    if(head == NULL)
        return 0;
    if(cmp == NULL)
        return -1;
    do
    {
        if(cmp(iterator->data, search))
            return 1;
    } while((iterator = iterator->next) != NULL);
    return 0;
}

/* @brief Return the data from the first item
 */
inline void* stack_peek(stack *s)
{
    return s->data;
}


#endif /* end of include guard: STACK_H */

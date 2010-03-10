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
#include "stack.h"

inline stack* stack_new(void)
{
    stack *s = malloc(sizeof(stack));
    s->data = NULL;
    s->next = NULL;
    return s;
}

inline stack* stack_push(void *data, stack* old)
{
    stack *s = stack_new();
    s->data = data;
    s->next = old;
    return s;
}

inline stack* stack_pop(stack* old)
{
    if(old == NULL) return NULL;
    stack *s = old->next;
    free(old);
    return s;
}

inline void* stack_peek(stack *s)
{
    return s->data;
}

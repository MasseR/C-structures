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
#ifndef LIST_RC86CSMV

#define LIST_RC86CSMV

/* A singly linked list */

struct list
{
    void *data;
    struct list *next;
};

typedef struct list* list_t;
typedef void (*func_t)(void *data);

list_t list_new(void *data);

list_t list_push_front(list_t list, void *data);
list_t list_pop_front(list_t list);

list_t list_push_tail(list_t list, void *data);
list_t list_pop_tail(list_t list);

list_t list_free(list_t list, func_t func);

void *list_get_front(list_t list);
void *list_get_tail(list_t list);
void *list_at(list_t list, unsigned int idx);

void list_foreach(list_t list, func_t func);

size_t list_size(list_t list);

#endif /* end of include guard: LIST_RC86CSMV */

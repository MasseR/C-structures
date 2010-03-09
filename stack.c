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

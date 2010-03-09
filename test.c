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
#include <cgreen.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "heap.h"

inline int heap_comp(void *a, void *b)
{
    assert(a != NULL);
    assert(b != NULL);
    return *(int*)a <= *(int*)b;
}

inline int stack_comp(void *a, void *b)
{
    return !strcmp((char*)a, (char*)b);
}

void test_stack_create_new(void)
{
    stack *s = stack_new();
    assert_equal(s->next, NULL);
    assert_equal(s->data, NULL);
    free(s);
}

/* Test creating a new first item */
void test_stack_push_new(void)
{
    int t = 5;
    stack *s = stack_push("hello", NULL);

    assert_equal(s->next, NULL);
    assert_string_equal(s->data, "hello");
    free(s);

    s = stack_push(&t, NULL);
    assert_equal(s->next, NULL);
    assert_equal(*(int*)(s->data), t);
    free(s);
}

/* Test with two items */
void test_stack_push_one(void)
{
    stack *first, *second;
    first = stack_push("world", NULL);
    second = stack_push("hello", first);

    assert_equal(first->next, NULL);
    assert_equal(second->next, first);

    assert_string_equal(first->data, "world");
    assert_string_equal(second->data, "hello");

    free(second);
    free(first);
}

void test_stack_push_two(void)
{
    stack *first, *second, *third;
    first = stack_push("world", NULL);
    second = stack_push("hello", first);
    third = stack_push("oh", second);

    assert_equal(first->next, NULL);
    assert_equal(second->next, first);
    assert_equal(third->next, second);

    assert_string_equal(first->data, "world");
    assert_string_equal(second->data, "hello");
    assert_string_equal(third->data, "oh");


    free(third);
    free(second);
    free(first);
}

void test_stack_peek(void)
{
    stack *s = stack_push("hello", NULL);
    assert_string_equal((char*)stack_peek(s), "hello");

    s = stack_push("world", s);
    assert_string_equal((char*)stack_peek(s), "world");

    free(s->next);
    free(s);
}

void test_stack_pop(void)
{
    stack *s = stack_push("world", NULL);
    s = stack_push("hello", s);

    assert_string_equal((char*)stack_peek(s), "hello");
    s = stack_pop(s);
    assert_string_equal((char*)stack_peek(s), "world");
    s = stack_pop(s);
    assert_equal(s, NULL);
}

void test_stack_pop_null(void)
{
    stack *s = stack_pop(NULL);
    assert_equal(s, NULL);
}

void test_stack_search_empty(void)
{
    assert_equal(stack_search(NULL, NULL, "foo"), 0);
}

void test_stack_search_one(void)
{
    stack *s = stack_push("hello", NULL);
    int result = 0;
    
    result = stack_search(s, stack_comp, "hello");
    assert_true(result);

    result = stack_search(s, stack_comp, "world");
    assert_false(result);

    free(s);
}

void test_stack_search_multiple(void)
{
    stack *s = NULL;
    int result = 0;

    s = stack_push("oh", NULL);
    s = stack_push("world", s);
    s = stack_push("hello", s);

    result = stack_search(s, stack_comp, "hello");
    assert_true(result);

    result = stack_search(s, stack_comp, "world");
    assert_true(result);

    result = stack_search(s, stack_comp, "oh");
    assert_true(result);

    result = stack_search(s, stack_comp, "foo");
    assert_false(result);

    s = stack_pop(s);
    s = stack_pop(s);
    s = stack_pop(s);
}

void test_stack_no_comparison_error(void)
{
    stack *s = stack_push("hello", NULL);

    assert_equal(stack_search(s, NULL, "hello"), -1);

    free(s);
}

TestSuite *stack_suite()
{
    TestSuite *suite = create_test_suite();
    add_test(suite, test_stack_create_new);
    add_test(suite, test_stack_push_new);
    add_test(suite, test_stack_push_one);
    add_test(suite, test_stack_push_two);
    add_test(suite, test_stack_peek);
    add_test(suite, test_stack_pop);
    add_test(suite, test_stack_pop_null);
    add_test(suite, test_stack_search_empty);
    add_test(suite, test_stack_search_one);
    add_test(suite, test_stack_search_multiple);
    add_test(suite, test_stack_no_comparison_error);
    return suite;
}

void test_heap_new(void)
{
    heap_t __attribute__((__unused__))heap = heap_new(5, &heap_comp);
}

void test_heap_new_has_correct_size(void)
{
    heap_t heap = heap_new(5, NULL);
    assert_equal(heap->size, 5);
}

void test_heap_new_has_correct_cmp(void)
{
    int a = 5, b = 6;
    heap_t heap = heap_new(5, &heap_comp);
    assert_equal(heap->cmp, &heap_comp);
    assert_equal(heap->cmp(&a, &b), 1);
    assert_equal(heap->cmp(&b, &a), 0);
}

void test_heap_new_has_n_null_nodes(void)
{
    size_t s = 5;
    int i;
    heap_t heap = heap_new(s, &heap_comp);
    for(i = 0; i < s; i++)
	assert_equal(heap->tree[i], NULL);
}

void test_heap_insert_1(void)
{
    int node = 2;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &node);
    assert_equal(*(int*)heap->tree[0], node);
}

void test_heap_insert_2(void)
{
    int a = 3, b = 2;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    /* The order should be 2, 3 */
    assert_equal(*(int*)heap->tree[0], b);
    assert_equal(*(int*)heap->tree[1], a);
}

void test_heap_insert_3(void)
{
    int a = 3, b = 2, c = 1;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    /* The order should be 1, 3, 2 */
    assert_equal(*(int*)heap->tree[0], c); // 1
    assert_equal(*(int*)heap->tree[1], a); // 3
    assert_equal(*(int*)heap->tree[2], b); // 2
}

void test_heap_insert_4(void)
{
    int a = 3, b = 2, c = 1, d = 0;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    heap_insert(heap, &d);
    /* The order should be 0, 1, 2, 3 */
    assert_equal(*(int*)heap->tree[0], d);
    assert_equal(*(int*)heap->tree[1], c);
    assert_equal(*(int*)heap->tree[2], b);
    assert_equal(*(int*)heap->tree[3], a);
}

void test_heap_insert_4_in_correct_order(void)
{
    int a = 3, b = 2, c = 1, d = 0;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &d);
    heap_insert(heap, &c);
    heap_insert(heap, &b);
    heap_insert(heap, &a);
    /* The order should be 0, 1, 2, 3 */
    assert_equal(*(int*)heap->tree[0], d);
    assert_equal(*(int*)heap->tree[1], c);
    assert_equal(*(int*)heap->tree[2], b);
    assert_equal(*(int*)heap->tree[3], a);
}

void test_heap_delete_size_1(void)
{
    int a = 5;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_remove(heap);
    assert_equal(heap->tree[0], NULL);
}

void test_heap_delete_size_2(void)
{
    int a = 5, b = 3;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    /* The order should be now b, a and after the removal operation a
     * should be in b's place; index 0 should be 5 */
    heap_remove(heap);
    assert_equal(*(int*)heap->tree[0], a);
}

void test_heap_delete_size_3(void)
{
    int a = 5, b = 3, c = 2;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    /* The order should be  c, a, b */
    heap_remove(heap);
    assert_equal(*(int*)heap->tree[0], b);
}

void test_heap_delete_size_4(void)
{
    int a = 3, b = 2, c = 1, d = 0;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    heap_insert(heap, &d);
    /* The order should be 0, 1, 2, 3 */
    heap_remove(heap);
    assert_equal(*(int*)heap->tree[0], c);
}

void test_heap_delete_size_5(void)
{
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    /* Causes the first swap to right */
    heap_t heap = heap_new(10, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    heap_insert(heap, &d);
    heap_insert(heap, &e);
    
    heap_remove(heap);
    assert_equal(*(int*)heap->tree[0], b);
    assert_equal(*(int*)heap->tree[1], d);
    assert_equal(*(int*)heap->tree[2], c);
    assert_equal(*(int*)heap->tree[3], e);
}

void test_heap_delete_from_right(void)
{
    int a = 1, b = 20, c = 5, d = 32, e = 36, f = 6;
    /* Causes the left side to be a lot heavier */
    heap_t heap = heap_new(10, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);
    heap_insert(heap, &d);
    heap_insert(heap, &e);
    heap_insert(heap, &f);
    heap_remove(heap);

    assert_equal(*(int*)heap->tree[0], 5);
    assert_equal(*(int*)heap->tree[1], 20);
    assert_equal(*(int*)heap->tree[2], 6);
    assert_equal(*(int*)heap->tree[3], 32);
    assert_equal(*(int*)heap->tree[4], 36);
}

TestSuite *heap_suite()
{
    TestSuite *suite = create_test_suite();
    add_test(suite, test_heap_new);
    add_test(suite, test_heap_new_has_correct_size);
    add_test(suite, test_heap_new_has_correct_cmp);
    add_test(suite, test_heap_new_has_n_null_nodes);
    add_test(suite, test_heap_insert_1);
    add_test(suite, test_heap_insert_2);
    add_test(suite, test_heap_insert_3);
    add_test(suite, test_heap_insert_4);
    add_test(suite, test_heap_insert_4_in_correct_order);
    add_test(suite, test_heap_delete_size_1);
    add_test(suite, test_heap_delete_size_2);
    add_test(suite, test_heap_delete_size_3);
    add_test(suite, test_heap_delete_size_4);
    add_test(suite, test_heap_delete_size_5);
    add_test(suite, test_heap_delete_from_right);
    return suite;
}

int main(int argc, const char *argv[])
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, stack_suite());
    add_suite(suite, heap_suite());

    if(argc > 1)
    {
        return run_single_test(suite, (char*)argv[1],
                create_text_reporter());
    }
    return run_test_suite(suite, create_text_reporter());
}

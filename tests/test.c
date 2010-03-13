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
#include "../src/mstack.h"
#include "../src/mheap.h"
#include "../src/mlist.h"

static int deletions;

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

inline void counter_increase(void *a)
{
    if(a != NULL)
	deletions++;
}

void test_stack_create_new(void)
{
    stack_t s = stack_new();
    assert_equal(s->next, NULL);
    assert_equal(s->data, NULL);
    free(s);
}

/* Test creating a new first item */
void test_stack_push_new(void)
{
    int t = 5;
    stack_t s = stack_push("hello", NULL);

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
    stack_t first, second;
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
    stack_t first, second, third;
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
    stack_t s = stack_push("hello", NULL);
    assert_string_equal((char*)stack_peek(s), "hello");

    s = stack_push("world", s);
    assert_string_equal((char*)stack_peek(s), "world");

    free(s->next);
    free(s);
}

void test_stack_pop(void)
{
    stack_t s = stack_push("world", NULL);
    s = stack_push("hello", s);

    assert_string_equal((char*)stack_peek(s), "hello");
    s = stack_pop(s);
    assert_string_equal((char*)stack_peek(s), "world");
    s = stack_pop(s);
    assert_equal(s, NULL);
}

void test_stack_pop_null(void)
{
    stack_t s = stack_pop(NULL);
    assert_equal(s, NULL);
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
    return suite;
}

void test_heap_new(void)
{
    heap_t __attribute__((__unused__))heap = heap_new(5, &heap_comp);
}

void test_heap_new_has_correct_size(void)
{
    heap_t heap = heap_new(5, &heap_comp);
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

void test_heap_new_has_zero_nodes(void)
{
    heap_t heap = heap_new(5, &heap_comp);
    assert_equal(heap->nodes, 0);
}

void test_heap_new_has_n_null_nodes(void)
{
    size_t s = 5;
    unsigned int i;
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

void test_heap_inserting_increases_nodes(void)
{
    int a = 5, b = 2;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);
    assert_equal(heap->nodes, 2);
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

void test_heap_deleting_decreases_nodes(void)
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

    assert_equal(heap->nodes, 4);
}

void test_heap_insert_1_peek(void)
{
    int a = 5;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);

    assert_equal(*(int*)heap_peek(heap), 5);
}

void test_heap_insert_2_peek(void)
{
    int a = 5, b = 1;
    heap_t heap = heap_new(5, &heap_comp);
    heap_insert(heap, &a);
    heap_insert(heap, &b);

    assert_equal(*(int*)heap_peek(heap), 1);
}

void test_heap_set_delete_func(void)
{
    heap_t heap = heap_new(5, &heap_comp);
    heap_set_on_exit(heap, &counter_increase);
    assert_equal(heap->exfunc, &counter_increase);
}

void test_heap_free(void)
{
    /* This should also be checked with valgrind, to make sure the entire
     * struct has been free'd */
    int a = 5, b = 3, c = 1;
    deletions = 0;
    heap_t heap = heap_new(5, &heap_comp);
    heap_set_on_exit(heap, &counter_increase);

    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);

    heap_free(heap);
    assert_equal(deletions, 3);
}

void test_heap_free_no_exit_func(void)
{
    int a = 5, b = 3, c = 1;
    deletions = 0;
    heap_t heap = heap_new(5, &heap_comp);

    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);

    heap_free(heap);
    assert_equal(deletions, 0);
}

void test_heap_remove_calls_exit(void)
{
    int a = 5, b = 3, c = 2;
    heap_t heap = heap_new(5, &heap_comp);

    deletions = 0;

    heap_set_on_exit(heap, &counter_increase);

    heap_insert(heap, &a);
    heap_insert(heap, &b);
    heap_insert(heap, &c);

    heap_remove(heap);
    assert_equal(deletions, 1);
    heap_remove(heap);
    assert_equal(deletions, 2);
    heap_remove(heap);
    assert_equal(deletions, 3);
}

void test_heap_sort(void)
{
    unsigned int i;
    size_t size = 5;
    void **array = NULL;
    array = malloc(sizeof(int*) * size);
    for(i = 0; i < size; i++)
	array[i] = malloc(sizeof(int));
    *(int*)array[0] = 3;
    *(int*)array[1] = 1;
    *(int*)array[2] = 9;
    *(int*)array[3] = 5;
    *(int*)array[4] = 8;

    heap_sort((void*)array, size, heap_comp);
    assert_equal(*(int*)array[0], 1);
    assert_equal(*(int*)array[1], 3);
    assert_equal(*(int*)array[2], 5);
    assert_equal(*(int*)array[3], 8);
    assert_equal(*(int*)array[4], 9);

    for(i = 0; i < size; i++)
	free(array[i]);
    free(array);
}

TestSuite *heap_suite()
{
    TestSuite *suite = create_test_suite();
    add_test(suite, test_heap_new);
    add_test(suite, test_heap_new_has_correct_size);
    add_test(suite, test_heap_new_has_zero_nodes);
    add_test(suite, test_heap_new_has_correct_cmp);
    add_test(suite, test_heap_new_has_n_null_nodes);
    add_test(suite, test_heap_insert_1);
    add_test(suite, test_heap_insert_2);
    add_test(suite, test_heap_insert_3);
    add_test(suite, test_heap_insert_4);
    add_test(suite, test_heap_insert_4_in_correct_order);
    add_test(suite, test_heap_inserting_increases_nodes);
    add_test(suite, test_heap_delete_size_1);
    add_test(suite, test_heap_delete_size_2);
    add_test(suite, test_heap_delete_size_3);
    add_test(suite, test_heap_delete_size_4);
    add_test(suite, test_heap_delete_size_5);
    add_test(suite, test_heap_delete_from_right);
    add_test(suite, test_heap_deleting_decreases_nodes);
    add_test(suite, test_heap_insert_1_peek);
    add_test(suite, test_heap_insert_2_peek);
    add_test(suite, test_heap_set_delete_func);
    add_test(suite, test_heap_remove_calls_exit);
    add_test(suite, test_heap_free);
    add_test(suite, test_heap_free_no_exit_func);
    add_test(suite, test_heap_sort);
    return suite;
}

void test_list_new(void)
{
    list_t __attribute__((__unused__))list = list_new(NULL);
}

void test_list_new_has_data(void)
{
    int a = 5;
    list_t list = list_new(&a);
    assert_equal(*(int*)list->data, 5);
}

void test_list_push_front_with_null_creates_new(void)
{
    int a = 5;
    list_t list = list_push_front(NULL, &a);
    assert_equal(*(int*)list->data, 5);
    assert_equal(list->next, NULL);
}

void test_list_push_front_2(void)
{
    int a = 5, b = 3;
    list_t prev = list_push_front(NULL, &a);
    list_t list = list_push_front(prev, &b);
    assert_equal(*(int*)list->data, 3);
    assert_equal(list->next, prev);
    assert_equal(*(int*)list->next->data, 5);
    assert_equal(list->next->next, NULL);
}

void test_list_new_next_is_null(void)
{
    int a = 5;
    list_t list = list_new(&a);
    assert_equal(list->next, NULL);
}

void test_list_push_tail_with_null_creates_new(void)
{
    int a = 5;
    list_t list = list_push_tail(NULL, &a);
    assert_equal(*(int*)list->data, 5);
    assert_equal(list->next, NULL);
}

void test_list_push_tail_2_inserts_end(void)
{
    int a = 5, b = 3;
    list_t first = list_push_tail(NULL, &a);
    list_t second = list_push_tail(first, &b);
    assert_equal(first, second);
    assert_equal(*(int*)first->next->data, 3);
    assert_equal(*(int*)first->data, 5);
}

void test_list_push_tail_3_inserts_end(void)
{
    int a = 5, b = 3, c = 4;
    list_t first = list_push_tail(NULL, &a);
    list_t second = list_push_tail(first, &b);
    list_t third = list_push_tail(second, &c);
    assert_equal(first, second);
    assert_equal(first, third);
    assert_equal(*(int*)first->next->next->data, 4);
    assert_equal(*(int*)first->next->data, 3);
    assert_equal(*(int*)first->data, 5);
}

void test_list_push_tail_4_inserts_end(void)
{
    int a = 5, b = 3, c = 4, d = 6;
    list_t first = list_push_tail(NULL, &a);
    list_t second = list_push_tail(first, &b);
    list_t third = list_push_tail(second, &c);
    list_t fourth = list_push_tail(third, &d);
    assert_equal(first, second);
    assert_equal(first, third);
    assert_equal(first, fourth);
    assert_equal(*(int*)first->next->next->next->data, 6);
    assert_equal(*(int*)first->next->next->data, 4);
    assert_equal(*(int*)first->next->data, 3);
    assert_equal(*(int*)first->data, 5);
}


void test_list_push_front_size_0(void)
{
    list_t list = NULL;
    assert_equal(list_size(list), 0);
}

void test_list_push_front_size_1(void)
{
    list_t list = NULL;
    list = list_push_front(list, NULL);
    assert_equal(list_size(list), 1);
}

void test_list_push_front_size_2(void)
{
    list_t list = NULL;
    list = list_push_front(list, NULL);
    list = list_push_front(list, NULL);
    assert_equal(list_size(list), 2);
}

void test_list_push_front_size_3(void)
{
    list_t list = NULL;
    list = list_push_front(list, NULL);
    list = list_push_front(list, NULL);
    list = list_push_front(list, NULL);
    assert_equal(list_size(list), 3);
}

void test_list_get_front(void)
{
    int a = 5, b = 3;
    list_t list = list_push_front(NULL, &a);
    list = list_push_front(list, &b);
    assert_equal(*(int*)list_get_front(list), 3);
}

void test_list_get_tail(void)
{
    int a = 5, b = 3;
    list_t list = list_push_tail(NULL, &a);
    list = list_push_tail(list, &b);
    assert_equal(*(int*)list_get_tail(list), 3);
}

void test_list_pop_front_1_returns_null(void)
{
    list_t list = NULL;
    int a = 5;
    list = list_push_front(list, &a);
    list = list_pop_front(list);
    assert_equal(list, NULL);
    assert_equal(list_size(list), 0);
}

void test_list_pop_front_2_returns_second(void)
{
    int a = 5, b = 3;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_push_front(list, &b);
    list = list_pop_front(list);
    assert_equal(*(int*)list->data, 5);
    assert_equal(list_size(list), 1);
}

void test_list_pop_tail_1_returns_null(void)
{
    int a = 5;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_pop_tail(list);
    assert_equal(list, NULL);
    assert_equal(list_size(list), 0);
}

void test_list_pop_tail_2_returns_first(void)
{
    int a = 5, b = 3;
    list_t list = NULL, after_pop = NULL;
    list = list_push_tail(list, &a);
    list = list_push_tail(list, &b);
    after_pop = list_pop_tail(list);
    assert_equal(list, after_pop);
    assert_equal(list_size(after_pop), 1);
    assert_equal(*(int*)list_get_tail(after_pop), 5);
}

void test_list_pop_tail_3_returns_first(void)
{
    int a = 5, b = 3, c = 4;
    list_t list = NULL, after_pop = NULL;
    list = list_push_tail(list, &a);
    list = list_push_tail(list, &b);
    list = list_push_tail(list, &c);
    after_pop = list_pop_tail(list);
    assert_equal(list, after_pop);
    assert_equal(list_size(after_pop), 2);
    assert_equal(*(int*)list_get_tail(after_pop), 3);
}

void test_list_foreach_size_1(void)
{
    int a = 5;
    deletions = 0;
    list_t list = list_push_front(NULL, &a);
    list_foreach(list, &counter_increase);
    assert_equal(deletions, 1);
}

void test_list_foreach_size_2(void)
{
    int a = 5, b = 3;
    deletions = 0;
    list_t list = list_push_front(NULL, &a);
    list = list_push_front(list, &b);
    list_foreach(list, &counter_increase);
    assert_equal(deletions, 2);
}

void test_list_foreach_size_3(void)
{
    int a = 5, b = 3, c = 4;
    deletions = 0;
    list_t list = list_push_front(NULL, &a);
    list = list_push_front(list, &b);
    list = list_push_front(list, &c);
    list_foreach(list, &counter_increase);
    assert_equal(deletions, 3);
}

void test_list_foreach_no_callback(void)
{
    list_t list = NULL;
    list = list_push_front(list, NULL);
    list = list_push_front(list, NULL);
    list = list_push_front(list, NULL);
    list_foreach(list, NULL);
}

void test_list_free_calls_foreach(void)
{
    int a = 5, b = 3, c = 4;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_push_front(list, &b);
    list = list_push_front(list, &c);
    list = list_free(list, &counter_increase);
    assert_equal(list, NULL);
    assert_equal(deletions, 3);
}

void test_list_free_does_not_calls_foreach(void)
{
    int a = 5, b = 3, c = 4;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_push_front(list, &b);
    list = list_push_front(list, &c);
    list = list_free(list, NULL);
    assert_equal(list, NULL);
    /* Should segfault if tries to call the func */
}

void test_list_at_in_range(void)
{
    int a = 5, b = 3, c = 4;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_push_front(list, &b);
    list = list_push_front(list, &c);
    assert_equal(*(int*)list_at(list, 0), 4);
    assert_equal(*(int*)list_at(list, 1), 3);
    assert_equal(*(int*)list_at(list, 2), 5);
}

void test_list_at_out_range(void)
{
    int a = 5, b = 3, c = 4;
    list_t list = NULL;
    list = list_push_front(list, &a);
    list = list_push_front(list, &b);
    list = list_push_front(list, &c);
    assert_equal(list_at(list, 3), NULL);
    assert_equal(list_at(list, 4), NULL);
}

TestSuite *list_suite()
{
    TestSuite *suite = create_test_suite();
    add_test(suite, test_list_new);
    add_test(suite, test_list_new_has_data);
    add_test(suite, test_list_new_next_is_null);
    add_test(suite, test_list_push_front_with_null_creates_new);
    add_test(suite, test_list_push_front_2);
    add_test(suite, test_list_push_tail_with_null_creates_new);
    add_test(suite, test_list_push_tail_2_inserts_end);
    add_test(suite, test_list_push_tail_3_inserts_end);
    add_test(suite, test_list_push_tail_4_inserts_end);
    add_test(suite, test_list_push_front_size_0);
    add_test(suite, test_list_push_front_size_1);
    add_test(suite, test_list_push_front_size_2);
    add_test(suite, test_list_push_front_size_3);
    add_test(suite, test_list_get_front);
    add_test(suite, test_list_get_tail);
    add_test(suite, test_list_pop_front_1_returns_null);
    add_test(suite, test_list_pop_front_2_returns_second);
    add_test(suite, test_list_pop_tail_1_returns_null);
    add_test(suite, test_list_pop_tail_2_returns_first);
    add_test(suite, test_list_pop_tail_3_returns_first);
    add_test(suite, test_list_foreach_size_1);
    add_test(suite, test_list_foreach_size_2);
    add_test(suite, test_list_foreach_size_3);
    add_test(suite, test_list_foreach_no_callback);
    add_test(suite, test_list_free_calls_foreach);
    add_test(suite, test_list_free_does_not_calls_foreach);
    add_test(suite, test_list_at_in_range);
    add_test(suite, test_list_at_out_range);
    return suite;
}

int main(int argc, const char *argv[])
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, stack_suite());
    add_suite(suite, heap_suite());
    add_suite(suite, list_suite());

    if(argc > 1)
    {
        return run_single_test(suite, (char*)argv[1],
                create_text_reporter());
    }
    return run_test_suite(suite, create_text_reporter());
}

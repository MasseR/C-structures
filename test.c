#include <cgreen.h>
#include <string.h>
#include "stack.h"

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

int main(int argc, const char *argv[])
{
    TestSuite *suite = create_test_suite();
    add_suite(suite, stack_suite());

    if(argc > 1)
    {
        return run_single_test(suite, (char*)argv[1],
                create_text_reporter());
    }
    return run_test_suite(suite, create_text_reporter());
}

#include <stdio.h>
#include "printer.h"

void show_fail(TestReporter __attribute__((__unused__))*reporter, const char * file, int line, const char *message, va_list arguments)
{
    printf("%s:%d: Failed. ", file, line);
    vprintf(message, arguments);
    printf("\n");
}

void reporter_finish_suite(TestReporter *reporter, const char *name)
{
    reporter_finish(reporter, name);
}
void reporter_start_suite(TestReporter *reporter, const char *name)
{
    reporter_start(reporter, name);
}

void show_incomplete(TestReporter __attribute__((__unused__))*reporter, const char *name)
{
    printf("Test %s failed to complete\n", name);
}

void show_destroy_reporter(TestReporter *reporter)
{
    printf("Test finished\n");
    printf("%d tests passed\n", reporter->passes);
    printf("%d tests failed\n", reporter->failures);
    printf("%d tests exception\n", reporter->exceptions);
    destroy_reporter(reporter);
}

TestReporter *create_compiler_reporter()
{
    TestReporter *reporter = create_reporter();
    reporter->finish_suite = &reporter_finish_suite;
    reporter->start_suite = &reporter_start_suite;
    reporter->show_fail = &show_fail;
    reporter->show_incomplete = &show_incomplete;
    reporter->destroy = &show_destroy_reporter;
    return reporter;
}

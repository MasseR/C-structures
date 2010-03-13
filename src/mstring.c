#include <stdlib.h>
#include <string.h>
#include "mstring.h"

int levenshtein(const char *a, const char *b)
{
    size_t m, n;
    if(a == NULL || b == NULL)
	return -1;
    n = strlen(a);
    m = strlen(b);
    if(n == 0) return m;
    if(m == 0) return n;
    return 0;
}

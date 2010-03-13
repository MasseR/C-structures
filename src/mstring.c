#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "mstring.h"

int levenshtein(const char *a, const char *b)
{
    size_t m, n, sizea, sizeb;
    mbstate_t *state = NULL;
    wchar_t *wa = NULL, *wb = NULL;
    /* Check whether either one is null or if they are the same */
    if(a == NULL || b == NULL) return -1;
    if(strcmp(a, b) == 0) return 0;
    /* Convert to wide character */
    sizea = strlen(a);
    sizeb = strlen(b);
    wa = malloc(sizeof(wchar_t) * sizea);
    wb = malloc(sizeof(wchar_t) * sizeb);
    n = mbsrtowcs(wa, &a, sizea, state);
    m = mbsrtowcs(wb, &b, sizeb, state);
    if(n == 0)
    {
	free(wa);
	free(wb);
	return m;
    }
    if(m == 0)
    {
	free(wa);
	free(wb);
	return n;
    }
    return -1;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "mstring.h"

#define COST(a, b) ((a) == (b)) ? 0 : 1

static int min(int a, int b, int c)
{
    int min = a;
    if(b < min)
	min = b;
    if(c < min)
	min = c;
    return min;
}

int levenshtein(const char *a, const char *b)
{
    /* Check whether either one is null or if they are the same */
    if(a == NULL || b == NULL) return -1;
    if(strcmp(a, b) == 0) return 0;

    unsigned int i, j;
    size_t m, n, sizea, sizeb, sizetemp;
    mbstate_t *state = NULL;
    wchar_t *wa = NULL, *wb = NULL, *wtemp = NULL;

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

    /* If the matrix would be wider, do it the other way around */
    if(n < m)
    {
	sizetemp = m;
	wtemp = wa;
	m = n;
	n = sizetemp;
	wa = wb;
	wb = wtemp;
    }

    /* Create n*m matrix and set first column and row to 0..n */
    int matrix[n+1][m+1];
    for(i = 0; i <= n; i++)
    {
	for(j = 0; j <= m; j++)
	    matrix[i][j] = 0;
    }
    for(i = 0; i <= n; i++)
	matrix[i][0] = i;
    for(i = 0; i <= m; i++)
	matrix[0][i] = i;

    for(i = 1; i <= n; i++)
    {
	for(j = 1; j <= m; j++)
	{
	    int cost = COST(wa[i-1], wb[j-1]);
	    int left = matrix[i-1][j] + 1;
	    int right = matrix[i-1][j] + 1;
	    int leftright = matrix[i-1][j-1] + cost;
	    matrix[i][j] = min(left, right, leftright);
	}
    }

    return matrix[n][m];
}


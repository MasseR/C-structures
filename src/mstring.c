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

    unsigned int i, j, cost, left, up, leftup;
    size_t m, n, sizea, sizeb;
    mbstate_t *state = NULL;
    wchar_t *wa = NULL, *wb = NULL;

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
	    cost = COST(wa[i-1], wb[j-1]);
	    left = matrix[i-1][j] + 1;
	    up = matrix[i][j-1] + 1;
	    leftup = matrix[i-1][j-1] + cost;
	    matrix[i][j] = min(left, up, leftup);
	}
    }

    return matrix[n][m];
}


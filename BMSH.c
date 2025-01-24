#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BMSH.h"

void BMHS(TipoTexto T, long n, TipoPadrao P, long m) {
    long i, j, k, d[MAXCHAR];
    for (j = 0; j < MAXCHAR; j++) {
        d[j] = m;
    }
    for (j = 1; j <= m - 1; j++) {
        d[P[j - 1]] = m - j;
    }
    i = m;
    while (i <= n) {
        k = i;
        j = m;
        while (T[k - 1] == P[j - 1] && j > 0) {
            k--;
            j--;
        }
        if (j == 0) {
            printf("O padrao ocorre na posicao: %ld\n", k + 1);
        }
        i += d[T[i - 1]];
    }
}

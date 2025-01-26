#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BMSH.h"

void BMHS(TipoTexto T, long n, TipoPadrao P, long m) {
    long i, j, k, d[MAX_CHAR];
    for (j = 0; j < MAX_CHAR; j++) {
        d[j] = m;
    }
    for (j = 1; j <= m - 1; j++) {
        d[P[j - 1]] = m - j;
    }
    i = m;
    while (i <= n) {
        k = i;
        j = m;
        while(!isprint((unsigned char)T[k - 1])) {i++;k++;}
        while (T[k - 1] == P[j - 1] && j > 0) {
            k--;
            j--;
        }
        if (j == 0) {
            printf("(BMHS) O padrao ocorre na posicao: %ld\n", k + 1);
        }
        i += d[T[i - 1]];
    }
}

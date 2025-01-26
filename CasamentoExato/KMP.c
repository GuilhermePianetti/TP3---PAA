#include <stdio.h>
#include <stdlib.h>

#include "KMP.h"
#include "texto.h"
#include "KMP.h"

#include <stdio.h>
#include <string.h>

void LPS(TipoPadrao P, int m, int *lps) {
    int length = 0; // Comprimento do prefixo/sufixo mais longo
    int i = 1;
    lps[0] = 0; // Primeiro elemento sempre é 0

    // Constrói a tabela LPS
    while (i < m) {
        if (P[i] == P[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Função para realizar a busca usando KMP
void KMP(TipoTexto T, long n, TipoPadrao P, long m) {

    // Cria a tabela LPS
    int lps[MAXTAMPADRAO];
    LPS(P, m, lps);

    int i = 0; // Índice do texto
    int j = 0; // Índice do padrão

    while (i < n) {
        if (P[j] == T[i]) {
            i++;
            j++;
        }

        if (j == m) {
            printf("(KMP) O padrao ocorre na posicao: %d\n", i - j + 1);
            j = lps[j - 1];
        } else if (i < n && P[j] != T[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

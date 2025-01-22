#ifndef KMP_H
#define KMP_H

#include "texto.h"

void LPS(TipoPadrao P, int m, int *lps);
void KMP(TipoTexto T, long n, TipoPadrao P, long m);

#endif // KMP_H
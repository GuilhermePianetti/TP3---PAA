#ifndef CIFRA_H
#define CIFRA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void criptografar(const char *arquivoEntrada, const char *arquivoSaida, int chave);
void descriptografar(const char *arquivoEntrada, const char *arquivoSaida, int chave);
void gerarChaveAleatoria(const char *arquivoEntrada, const char *arquivoSaida);
void analisarFrequencias(const char *arquivoEntrada, int *frequencias);
void mostrarFrequencias(int *frequencias, int totalCaracteres);
int adivinharChave(int *frequencias);

#endif
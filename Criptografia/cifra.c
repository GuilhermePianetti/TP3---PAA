#include "cifra.h"
#include <float.h>
#include <string.h>
#include <math.h>

#define TAM_ALFABETO 26

float frequenciasLingua[] = {14.63, 1.04, 3.88, 4.99, 12.57, 1.02, 1.30, 1.28, 6.18, 0.40, 
                                 0.02, 2.78, 4.74, 5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 
                                 4.63, 1.67, 0.01, 0.21, 0.01, 0.47};

// Função que criptografa um arquivo de entrada e salva o resultado em um arquivo de saída
void criptografar(const char *arquivoEntrada, const char *arquivoSaida, int chave) {
    FILE *entrada = fopen(arquivoEntrada, "r");
    char caminhoRelativo[100] = "Outputs/";
    FILE *saida = fopen(strcat(caminhoRelativo, arquivoSaida), "w");
    if(!entrada || !saida){
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char c;
    while((c = fgetc(entrada)) != EOF){
        if(c >= 'a' && c <= 'z'){
            c = ((c - 'a' + chave) % TAM_ALFABETO) + 'a';
        }else if(c >= 'A' && c <= 'Z'){
            c = ((c - 'A' + chave) % TAM_ALFABETO) + 'A';
        }
        fputc(c, saida);
    }

    fclose(entrada);
    fclose(saida);
}

// Função que descriptografa um arquivo de entrada e salva o resultado em um arquivo de saída
void descriptografar(const char *arquivoEntrada, const char *arquivoSaida, int chave){
    criptografar(arquivoEntrada, arquivoSaida, TAM_ALFABETO - (chave % TAM_ALFABETO));
}

// Função que gera uma chave aleatória e criptografa um arquivo de entrada, salvando o resultado em um arquivo de saída
void gerarChaveAleatoria(const char *arquivoEntrada, const char *arquivoSaida){
    srand(time(NULL));
    int chave = rand() % TAM_ALFABETO;
    printf("Chave aleatoria gerada: %d\n", chave);
    criptografar(arquivoEntrada, arquivoSaida, chave);
}

// Função que analisa as frequências de caracteres em um arquivo de entrada
void analisarFrequencias(const char *arquivoEntrada, int *frequencias){
    FILE *entrada = fopen(arquivoEntrada, "r");
    if(!entrada){
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    memset(frequencias, 0, TAM_ALFABETO * sizeof(int));
    char c;
    while((c = fgetc(entrada)) != EOF){
        if(c >= 'a' && c <= 'z'){
            frequencias[c - 'a']++;
        }else if(c >= 'A' && c <= 'Z'){
            frequencias[c - 'A']++;
        }
    }

    fclose(entrada);
}

// Função que mostra as frequências de caracteres e a chave mais provável de um arquivo de entrada
void mostrarFrequencias(int *frequencias, int totalCaracteres){
    if(totalCaracteres == 0){
        printf("Nenhum caractere encontrado\n");
        return;
    }

    printf("Frequencias:\n");
    for(char c = 'a'; c <= 'z'; c++){
        int count = frequencias[c - 'a'];
        float percentual = ((float)count / totalCaracteres) * 100;
        printf("%c: %d (%.2f%%)\n", c, count, percentual);
    }
}

// Função que adivinha a chave de criptografia de um arquivo de entrada
int adivinharChave(int *frequencias){    
    int total = 0;
    for (int i = 0; i < TAM_ALFABETO; i++) {
        total += frequencias[i];
    }

    int chaveMaisProvavel = 0;
    float melhorDiferenca = FLT_MAX;

    for (int shift = 0; shift < TAM_ALFABETO; shift++) {
        float diferenca = 0.0;
        for (int i = 0; i < TAM_ALFABETO; i++) {
            int index = (i + shift) % TAM_ALFABETO;
            float porcentagem = (float)frequencias[index] / total * 100;
            diferenca += fabs(porcentagem - frequenciasLingua[i]);
        }

        if (diferenca < melhorDiferenca) {
            melhorDiferenca = diferenca;
            chaveMaisProvavel = shift;
        }
    }

    return chaveMaisProvavel;
}


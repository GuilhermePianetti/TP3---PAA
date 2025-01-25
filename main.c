#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "texto.h"
#include "BMSH.h"
#include "KMP.h"

// Função para contar o número de linhas em um arquivo
int contarLinhas(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        return 0; // Se o arquivo não existir, consideramos 0 linhas
    }

    int linhas = 0;
    int ch;
    while ((ch = fgetc(arquivo)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }
    fclose(arquivo);
    return linhas;
}

int main() {
    struct timespec start1, end1;
    struct timespec start2, end2;

    char *nomeArquivo1 = "dados1";
    char *nomeArquivo2 = "dados2";

    int linhas1 = contarLinhas(nomeArquivo1);
    int linhas2 = contarLinhas(nomeArquivo2);

    TipoTexto T;
    TipoPadrao P[MAXTAMPADRAO];

    FILE *file;
    char nameFile[256];
    char name[256] = "";

    printf("Digite o nome do arquivo de texto: ");
    scanf("%s", nameFile);

    strcat(name, nameFile);

    file = fopen(nameFile, "r");
    if (file == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return 1;
    }

    size_t bytesRead = fread(T, sizeof(char), MAXTAMTEXTO - 1, file);
    T[bytesRead] = '\0';
    fclose(file);

    printf("Digite o padrao: ");
    scanf("%s", P);

    int n = strlen(T);
    int m = strlen(P);

    clock_gettime(CLOCK_MONOTONIC, &start1);
    BMHS(T, n, P, m);
    clock_gettime(CLOCK_MONOTONIC, &end1);

    clock_gettime(CLOCK_MONOTONIC, &start2);
    KMP(T, n, P, m);
    clock_gettime(CLOCK_MONOTONIC, &end2);

    double time1 = (end1.tv_sec - start1.tv_sec) + 
                        (end1.tv_nsec - start1.tv_nsec) / 1e9;

    double time2 = (end2.tv_sec - start2.tv_sec) + 
                        (end2.tv_nsec - start2.tv_nsec) / 1e9;

    printf("Tempo de execução do BMHS: %lf\n", time1);
    printf("Tempo de execução do KMP: %lf\n", time2);

    // Abre os arquivos no modo de append para adicionar os resultados
    FILE *arquivo1 = fopen(nomeArquivo1, "a");
    if (arquivo1 == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1;
    }
    fprintf(arquivo1, "%d %lf\n", linhas1 + 1, time1);
    fclose(arquivo1);

    FILE *arquivo2 = fopen(nomeArquivo2, "a");
    if (arquivo2 == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return 1;
    }
    fprintf(arquivo2, "%d %lf\n", linhas2 + 1, time2);
    fclose(arquivo2);

    return 0;
}

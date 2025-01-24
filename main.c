#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "texto.h"
#include <time.h>
#include <sys/time.h>


#include "BMSH.h"
#include "KMP.h"

int main()
{

    struct timespec start1, end1;
    struct timespec start2, end2;
    int linhas1 = 0;
    char* nomeArquivo1 = "dados1";
    char* nomeArquivo2 = "dados2";
    FILE *arquivo1 = fopen(nomeArquivo1, "a");
    if (arquivo1 == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    int ch;
    while ((ch = fgetc(arquivo1)) != EOF)  {
        if (fgetc(arquivo1) == '\n') {
            linhas1++;
        }
    }

    FILE *arquivo2 = fopen(nomeArquivo2, "a");
    if (arquivo2 == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    int linhas2 = 0;
    while ((ch = fgetc(arquivo2)) != EOF)  {
        if (fgetc(arquivo2) == '\n') {
            linhas2++;
        }
    }


    TipoTexto T;
    TipoPadrao P[MAXTAMPADRAO];

    FILE *file;
    char nameFile[256];
    char name[256]; //= "../"; // Coloquei esse caminho antes pq não tava funcionando sem isso

    printf("Digite o nome do arquivo de texto: ");
    scanf("%s", nameFile);

    strcat(name, nameFile);

    file = fopen(nameFile, "r");
    if (file == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return 1;
    }

    size_t bytesRead = fread(T, sizeof(char), MAXTAMTEXTO - 1, file); //Lê o arquivo e armazena em T
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
  
    fprintf(arquivo1, "%d %lf\n", linhas1+1, time1);
    fprintf(arquivo2, "%d %lf\n", linhas2+1, time2);

    fclose(arquivo1);
    fclose(arquivo2);
    return 0;
}
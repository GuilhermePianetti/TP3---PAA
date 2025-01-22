#include <string.h>

#include "BMSH.c"
#include "KMP.c"

int main()
{

    TipoTexto T;
    TipoPadrao P[MAXTAMPADRAO];

    FILE *file;
    char nameFile[256];
    char name[256] = "../"; // Coloquei esse caminho antes pq não tava funcionando sem isso

    printf("Digite o nome do arquivo de texto: ");
    scanf("%255s", nameFile);

    strcat(name, nameFile);

    file = fopen(name, "r");
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

    BMHS(T, n, P, m);
    KMP(T, n, P, m);

    return 0;
}
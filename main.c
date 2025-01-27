#include <windows.h>
#include "CasamentoExato/texto.h"
#include "CasamentoExato/BMSH.h"
#include "CasamentoExato/KMP.h"
#include "Criptografia/cifra.h"

int contarLinhas(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        // Se o arquivo não existir, será criado posteriormente
        return 0;
    }

    int linhas = 0;
    char buffer[1024]; // Buffer para leitura de linhas
    while (fgets(buffer, sizeof(buffer), arquivo)) {
        linhas++;
    }

    fclose(arquivo);
    return linhas;
}

int main()
{
    int escolha, chave, frequencias[26];
    char arquivoEntrada[100], arquivoSaida[100];

    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Criptografar\n");
        printf("2 - Descriptografar\n");
        printf("3 - Gerar chave aleatoria\n");
        printf("4 - Analisar frequencias e adivinhar chave\n");
        printf("5 - Buscar padrao (Casamento exato)\n");
        printf("0 ou outro numero - Sair\n");
        printf("Opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("Digite o nome do arquivo de entrada contendo o texto(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoEntrada);
            printf("Digite a chave de criptografia(entre 1 e 25): ");
            scanf("%d", &chave);
            printf("Digite o nome do arquivo de saida(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoSaida);
            criptografar(arquivoEntrada, arquivoSaida, chave);
            printf("Texto criptografado salvo em 'Outputs/%s'.\n", arquivoSaida);
            break;
        case 2:
            printf("Digite o nome do arquivo de entrada contendo o texto(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoEntrada);
            printf("Digite a chave de descriptografia(entre 1 e 25): ");
            scanf("%d", &chave);
            printf("Digite o nome do arquivo de saida(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoSaida);
            descriptografar(arquivoEntrada, arquivoSaida, chave);
            printf("Texto descriptografado salvo em 'Outputs/%s'.\n", arquivoSaida);
            break;
        case 3:
            printf("Digite o nome do arquivo de entrada contendo o texto(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoEntrada);
            printf("Digite o nome do arquivo de saida(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoSaida);
            gerarChaveAleatoria(arquivoEntrada, arquivoSaida);
            printf("Texto criptografado com chave aleatoria salvo em 'Outputs/%s'.\n", arquivoSaida);
            break;
        case 4:
            printf("Digite o nome do arquivo de entrada contendo o texto(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoEntrada);
            int totalCaracteres = 0;
            analisarFrequencias(arquivoEntrada, frequencias);

            for (int i = 0; i < 26; i++)
            {
                totalCaracteres += frequencias[i];
            }

            mostrarFrequencias(frequencias, totalCaracteres);
            int chaveAdivinhada = adivinharChave(frequencias);
            printf("Chave adivinhada: %d\n", chaveAdivinhada);
            break;
        case 5:
            printf("Digite o nome do arquivo de entrada contendo o texto(Ex.: nomedoarquivo.txt): ");
            scanf("%s", arquivoEntrada);

            FILE *file = fopen(arquivoEntrada, "r");
            if (file == NULL)
            {
                printf("Problemas na abertura do arquivo\n");
                return 1;
            }

            TipoTexto T;
            TipoPadrao P[MAXTAMPADRAO];

            size_t bytesRead = fread(T, sizeof(char), MAXTAMTEXTO - 1, file);
            T[bytesRead] = '\0';
            fclose(file);

            printf("Digite o padrao: ");
            scanf("%s", P);

            int n = strlen(T);
            int m = strlen(P);

            LARGE_INTEGER inicio1, fim1, frequencia1, inicio2, fim2, frequencia2;
            double bmhs_time_sec, kmp_time_sec;

            QueryPerformanceFrequency(&frequencia1);
            QueryPerformanceCounter(&inicio1);
            BMHS(T, n, P, m);
            QueryPerformanceCounter(&fim1);

            QueryPerformanceFrequency(&frequencia2);
            QueryPerformanceCounter(&inicio2);
            KMP(T, n, P, m);
            QueryPerformanceCounter(&fim2);

            bmhs_time_sec = (double)(fim1.QuadPart - inicio1.QuadPart) / frequencia1.QuadPart;
            kmp_time_sec = (double)(fim2.QuadPart - inicio2.QuadPart) / frequencia2.QuadPart;

            printf("Tempo de execucao do BMHS: %.9f\n", bmhs_time_sec);
            printf("Tempo de execucao do KMP:  %.9f\n", kmp_time_sec);

            char *nomeArquivo1 = "dados1.txt";
            char *nomeArquivo2 = "dados2.txt";
            int linhas1 = 0, linhas2 = 0;

             linhas1 = contarLinhas(nomeArquivo1);
            linhas2 = contarLinhas(nomeArquivo2);

            FILE *arquivo1 = fopen(nomeArquivo1, "a");
            if (arquivo1 == NULL) {
                perror("Erro ao abrir o arquivo para escrita");
                return 1;
            }
            fprintf(arquivo1, "%d %lf\n", linhas1 + 1, bmhs_time_sec);
            fclose(arquivo1);

            FILE *arquivo2 = fopen(nomeArquivo2, "a");
            if (arquivo2 == NULL) {
                perror("Erro ao abrir o arquivo para escrita");
                return 1;
            }
            fprintf(arquivo2, "%d %lf\n", linhas2 + 1, kmp_time_sec);
            fclose(arquivo2);

            break;
        case 0:
            printf("Encerrando o programa...\n");
            break;
        default:
            printf("Opção invalida. Encerrando o programa...\n");
            break;
        }
    } while (escolha >= 1 && escolha <= 4);

    return 0;
}

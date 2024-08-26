#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h> // Necessário para o Windows
#define MKDIR(a) _mkdir(a)
#else
#include <unistd.h> // Necessário para sistemas Unix-like
#define MKDIR(a) mkdir(a, 0700)
#endif

void gerar_numeros(int *lista, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        lista[i] = rand() % 10001;
    }
}

int main()
{
    const char *pasta = "numeros_aleatorios";
    struct stat st = {0};

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Cria o diretório se não existir
    // Cria o diretório se não existir
    if (stat(pasta, &st) == -1)
    {
        if (MKDIR(pasta) != 0)
        {
            perror("Não foi possível criar o diretório");
            return 1;
        }
    }

    for (int n = 1000; n <= 100000; n += (n == 1000 ? 4000 : 5000))
    {
        int *lista = (int *)malloc(n * sizeof(int));
        if (lista == NULL)
        {
            perror("Não foi possível alocar memória");
            return 1;
        }

        gerar_numeros(lista, n);

        // Cria o nome do arquivo
        char nome_arquivo[100];
        snprintf(nome_arquivo, sizeof(nome_arquivo), "%s/numeros_%d.txt", pasta, n);

        FILE *arquivo = fopen(nome_arquivo, "w");
        if (arquivo == NULL)
        {
            perror("Não foi possível abrir o arquivo");
            free(lista);
            return 1;
        }

        for (int i = 0; i < n; i++)
        {
            fprintf(arquivo, "%d\n", lista[i]);
        }

        fclose(arquivo);
        free(lista);

        printf("Arquivo '%s' criado com sucesso.\n", nome_arquivo);
    }

    return 0;
}

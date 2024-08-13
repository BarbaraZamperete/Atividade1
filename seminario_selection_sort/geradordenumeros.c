#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_numeros(int lista[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        lista[i] = rand() % 10001;
    }
}

int main() {
    int n;
    const char *pasta = "numeros_aleatorios";

    printf("Digite o número de elementos: ");
    scanf("%d", &n);

    int lista[n];

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    gerar_numeros(lista, n);

    // Cria o diretório se não existir
    // struct stat st = {0};
    // if (stat(pasta, &st) == -1) {
    //     if (mkdir(pasta, 0700) != 0) {
    //         perror("Não foi possível criar o diretório");
    //         return 1;
    //     }
    // }

    // Cria o nome do arquivo
    char nome_arquivo[100];
    snprintf(nome_arquivo, sizeof(nome_arquivo), "%s/numeros_%d.txt", pasta, n);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        perror("Não foi possível abrir o arquivo");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", lista[i]);
    }

    fclose(arquivo);

    printf("Os números foram salvos em '%s'.\n", nome_arquivo);

    return 0;
}
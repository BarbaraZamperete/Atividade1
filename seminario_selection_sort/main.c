#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

// Estrutura para armazenar informações sobre cada arquivo
typedef struct {
    char filename[256];
    int quantity;
    double time_spent;
} FileInfo;

// Função de comparação para ordenar o array de structs
int compare_file_info(const void *a, const void *b) {
    return ((FileInfo *)a)->quantity - ((FileInfo *)b)->quantity;
}

void selection_sort(int vetor[], int max);

int main() {
    DIR *dir;
    struct dirent *entry;
    char input_filename[1024];
    char output_filename[1024];
    FILE *log_file;

    // Abrir o diretório de números aleatórios no diretório atual
    dir = opendir("./numeros_aleatorios");
    if (dir == NULL) {
        printf("Erro ao abrir o diretório ./numeros_aleatorios\n");
        return 1;
    }

    // Abrir arquivo de log para salvar os tempos de execução
    log_file = fopen("./log_tempo_execucao.txt", "w");
    if (log_file == NULL) {
        printf("Erro ao criar o arquivo de log\n");
        return 1;
    }

    // Armazenar informações sobre cada arquivo
    FileInfo file_infos[100];  // Ajustar o tamanho do array conforme necessário
    int file_count = 0;

    // Processar cada arquivo .txt no diretório
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt") != NULL) {
            // Construir o caminho completo dos arquivos de entrada e saída
            snprintf(input_filename, sizeof(input_filename), "./numeros_aleatorios/%s", entry->d_name);
            snprintf(output_filename, sizeof(output_filename), "./numeros_ordenados/ordenados_%s", entry->d_name);

            // Abrir o arquivo de entrada para leitura
            FILE *input_file = fopen(input_filename, "r");
            if (input_file == NULL) {
                printf("Erro ao abrir o arquivo %s\n", input_filename);
                continue;
            }

            // Determinar o número de elementos no arquivo
            int max = 0, num;
            while (fscanf(input_file, "%d", &num) != EOF) {
                max++;
            }

            // Retornar ao início do arquivo
            rewind(input_file);

            int vetor[max];
            for (int i = 0; i < max; i++) {
                fscanf(input_file, "%d", &vetor[i]);
            }

            // Fechar o arquivo de entrada
            fclose(input_file);

            // Medir o tempo de execução da ordenação
            clock_t start_time = clock();
            selection_sort(vetor, max);
            clock_t end_time = clock();

            // Calcular o tempo gasto em segundos
            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

            // Armazenar as informações no array
            strncpy(file_infos[file_count].filename, entry->d_name, sizeof(file_infos[file_count].filename) - 1);
            file_infos[file_count].filename[sizeof(file_infos[file_count].filename) - 1] = '\0';
            file_infos[file_count].quantity = max;
            file_infos[file_count].time_spent = time_spent;
            file_count++;

            // Abrir o arquivo de saída para escrita
            FILE *output_file = fopen(output_filename, "w");
            if (output_file == NULL) {
                printf("Erro ao abrir o arquivo %s\n", output_filename);
                continue;
            }

            // Escrever os números ordenados no arquivo
            for (int i = 0; i < max; i++) {
                fprintf(output_file, "%d\n", vetor[i]);
            }

            // Fechar o arquivo de saída
            fclose(output_file);
        }
    }

    // Fechar o diretório
    closedir(dir);

    // Ordenar o array de structs
    qsort(file_infos, file_count, sizeof(FileInfo), compare_file_info);

    // Escrever o log com os dados ordenados
    for (int i = 0; i < file_count; i++) {
        fprintf(log_file, "arquivo: %s, quantidade de numeros: %d, Tempo de execucao: %.2f segundos\n", file_infos[i].filename, file_infos[i].quantity, file_infos[i].time_spent);
    }

    // Fechar o arquivo de log
    fclose(log_file);

    printf("Processamento concluido. Verifique o arquivo de log para os tempos de execução.\n");

    return 0;
}

#include <stdlib.h>

void merge(int vetor[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Criar arrays temporários
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copiar dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = vetor[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vetor[middle + 1 + j];

    // Mesclar os arrays temporários de volta para o vetor[]
    int i = 0; // Índice inicial do primeiro subarray
    int j = 0; // Índice inicial do segundo subarray
    int k = left; // Índice inicial do array mesclado

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar os elementos restantes de L[], se houver
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copiar os elementos restantes de R[], se houver
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void merge_sort(int vetor[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Ordenar as duas metades
        merge_sort(vetor, left, middle);
        merge_sort(vetor, middle + 1, right);

        // Mesclar as duas metades
        merge(vetor, left, middle, right);
    }
}

#include <stdio.h>
#include <stdlib.h>

void selection_sort(int vetor[], int n) {
    int i, j, min, aux;

    /*
    Este loop percorre o vetor de 0 até n - 2. A ideia é que a cada iteração do loop externo, 
    o menor elemento da parte não ordenada do vetor seja movido para a posição correta.
    */
    for (i =0; i<(n-1); i++){
        min = i;
        for (j =i+1; j<n; j++) {
            /*
            Este loop percorre a parte não ordenada do vetor a partir do índice i + 1 até o final (n). 
            O objetivo é encontrar o menor elemento na parte não ordenada do vetor.
            */

           /*
           Se o elemento no índice j for menor do que o elemento no índice min, atualiza min para j. 
           Assim, ao final do loop interno, min conterá o índice do menor elemento na parte não ordenada.
           */
            if(vetor[j] <vetor[min]){
                min=j;
            }
        }

        /*
        Se o índice i não for o mesmo que o índice min, isso significa que o menor elemento encontrado 
        não está na posição i. Portanto, troca o elemento na posição i com o elemento na posição min 
        usando a variável auxiliar aux.
        */
        if (i != min){
            aux = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = aux;
        }
    }
}

#include "ordenacao.h"
#include <stdio.h> // Necessário para NULL, embora não usado aqui

// Função auxiliar para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int vetor[], int tam, long *comparacoes) {
    *comparacoes = 0; // Zera o contador
    int i, j, min_idx;

    for (i = 0; i < tam - 1; i++) {
        min_idx = i;
        // Procura o menor elemento no restante do vetor
        for (j = i + 1; j < tam; j++) {
            (*comparacoes)++; // Incrementa a cada comparação
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        
        // Troca o menor elemento encontrado com o primeiro elemento
        // da porção não ordenada (se for diferente)
        if (min_idx != i) {
            trocar(&vetor[min_idx], &vetor[i]);
        }
    }
}

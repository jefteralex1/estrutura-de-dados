#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

// Função auxiliar (privada) para criar um novo nó
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

No* inserir_no(No* raiz, int valor) {
    // 1. Caso base: árvore vazia ou nó folha
    if (raiz == NULL) {
        return criar_no(valor);
    }

    // 2. Recursão: desce pela árvore
    if (valor < raiz->valor) {
        raiz->esquerda = inserir_no(raiz->esquerda, valor);
    } else if (valor > raiz->valor) { 
        // Usamos 'else if' para evitar inserção de valores duplicados
        raiz->direita = inserir_no(raiz->direita, valor);
    }

    // Retorna a raiz (pode ser a original ou a nova, se a árvore estava vazia)
    return raiz;
}

// Percurso Em Ordem: Esquerda, Raiz, Direita
// Resultado deve ser os números em ordem crescente!
void percurso_em_ordem(No* raiz) {
    if (raiz != NULL) {
        percurso_em_ordem(raiz->esquerda);
        printf("%d ", raiz->valor);
        percurso_em_ordem(raiz->direita);
    }
}

int altura(No* raiz) {
    // Caso base: árvore vazia
    if (raiz == NULL) {
        return -1; // Altura de árvore vazia é -1
    } else {
        // Calcula a altura das subárvores
        int alt_esq = altura(raiz->esquerda);
        int alt_dir = altura(raiz->direita);

        // A altura da árvore é a maior altura da subárvore + 1
        if (alt_esq > alt_dir) {
            return alt_esq + 1;
        } else {
            return alt_dir + 1;
        }
    }
}

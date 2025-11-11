#ifndef ARVORE_H
#define ARVORE_H

// Estrutura do Nó da árvore
struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
};
typedef struct No No;

/**
 * Cria um novo nó da árvore.
 * (Função auxiliar interna, não precisa estar no .h se só arvore.c usar)
 */
// No* criar_no(int valor); // Pode ser privada em arvore.c

/**
 * Insere um novo valor na Árvore Binária de Busca (BST).
 * Retorna a raiz da árvore (modificada ou não).
 */
No* inserir_no(No* raiz, int valor);

/**
 * Exibe o percurso "Em Ordem" (In-Order) da árvore.
 * Esquerda -> Raiz -> Direita
 */
void percurso_em_ordem(No* raiz);

/**
 * Calcula a altura da árvore.
 * A altura de uma árvore vazia (NULL) é -1.
 * A altura de uma árvore com um único nó (raiz) é 0.
 */
int altura(No* raiz);

#endif

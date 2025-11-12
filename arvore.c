// Inclui o "contrato" (o arquivo de cabeçalho) que define o que é um 'No'
// (deve ter a 'struct No') e quais funções existem.
#include "arvore.h" 
// Para printf() (imprimir na tela)
#include <stdio.h> 
// Para malloc() (alocar memória) e exit() (parar o programa)
#include <stdlib.h> 

// --- Função 1: criar_no (Função Auxiliar) ---

// Esta é uma função "privada" (auxiliar). Ela não é chamada pelo main.c,
// ela apenas ajuda a 'inserir_no' a trabalhar.
// Sua única tarefa é criar um nó "recém-nascido".
No* criar_no(int valor) {
    // 1. Aloca (reserva) um espaço na memória do tamanho exato de um 'No'
    No* novo = (No*)malloc(sizeof(No));
    
    // 2. Checa se a alocação de memória falhou (ex: computador sem memória)
    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1); // Aborta o programa imediatamente
    }
    
    // 3. Preenche o novo nó
    novo->valor = valor;      // Coloca o valor (ex: 50) dentro do nó
    novo->esquerda = NULL;  // O nó "nasce" sem filhos à esquerda
    novo->direita = NULL;   // E sem filhos à direita
    
    // 4. Retorna o endereço do nó que acabou de criar
    return novo;
}

// --- Função 2: inserir_no (A Função Principal) ---

// Esta é a função mais importante e é RECURSIVA.
// Ela segue a regra principal da Árvore Binária de Busca (BST):
// "Se o valor for MENOR, vai para a ESQUERDA."
// "Se o valor for MAIOR, vai para a DIREITA."
No* inserir_no(No* raiz, int valor) {
    
    // 1. CASO BASE (A condição de parada da recursão)
    // Se a árvore (ou sub-árvore) estiver vazia (NULL)...
    // ...achamos o lugar certo! É aqui que o novo nó deve ser inserido.
    if (raiz == NULL) {
        // Cria um novo nó com o valor e o retorna
        return criar_no(valor); 
    }

    // 2. PASSO RECURSIVO (A "descida" na árvore)
    // Se a árvore NÃO estiver vazia, comparamos os valores:
    
    // Se o novo 'valor' for MENOR que o valor da 'raiz' atual...
    if (valor < raiz->valor) {
        // ...ele pertence à sub-árvore da ESQUERDA.
        // Chamamos a função DE NOVO, mas agora com 'raiz->esquerda'.
        // O resultado (o novo nó ou o ponteiro antigo) é "grudado" de volta na esquerda.
        raiz->esquerda = inserir_no(raiz->esquerda, valor);
        
    // Se o novo 'valor' for MAIOR que o valor da 'raiz' atual...
    } else if (valor > raiz->valor) { 
        // (Nota: 'else if' ignora valores duplicados. Se for igual, nada acontece)
        // ...ele pertence à sub-árvore da DIREITA.
        // Chamamos a função DE NOVO, mas com 'raiz->direita'.
        raiz->direita = inserir_no(raiz->direita, valor);
    }

    // 3. Retorno
    // Retorna o ponteiro da 'raiz' (que não mudou)
    // Isso é o que permite que a recursão "reconecte" a árvore
    return raiz;
}
// 

// --- Função 3: percurso_em_ordem (A "Prova") ---

// Esta função RECURSIVA visita os nós na ordem: Esquerda, Raiz, Direita.
// É por causa dessa regra que, em uma BST, os valores são
// impressos em ORDEM CRESCENTE.
void percurso_em_ordem(No* raiz) {
    // Condição de parada: só faz algo se o nó não for nulo
    if (raiz != NULL) {
        // 1. Visita o filho da ESQUERDA (vai o mais fundo à esquerda possível)
        percurso_em_ordem(raiz->esquerda);
        
        // 2. Visita a RAIZ (imprime o valor do nó atual)
        printf("%d ", raiz->valor);
        
        // 3. Visita o filho da DIREITA
        percurso_em_ordem(raiz->direita);
    }
}
// 

// --- Função 4: altura (Análise da Árvore) ---

// Função RECURSIVA para calcular a altura da árvore.
// Altura = O caminho mais longo da raiz até um nó folha (um nó sem filhos).
int altura(No* raiz) {
    
    // 1. CASO BASE (Condição de parada)
    // Por convenção, a altura de uma árvore vazia (NULL) é -1.
    // (Uma árvore com 1 nó teria altura 0)
    if (raiz == NULL) {
        return -1; 
    } else {
        // 2. PASSO RECURSIVO
        // Calcula a altura da sub-árvore esquerda
        int alt_esq = altura(raiz->esquerda);
        // Calcula a altura da sub-árvore direita
        int alt_dir = altura(raiz->direita);

        // 3. Cálculo
        // A altura do nó ATUAL é a MAIOR altura entre seus filhos, MAIS 1 (para contar ele mesmo).
        
        // Se a altura da esquerda for maior...
        if (alt_esq > alt_dir) {
            return alt_esq + 1; // ...retorna altura da esquerda + 1
        } else {
            // ...senão (se a direita for maior ou igual), retorna altura da direita + 1
            return alt_dir + 1; 
        }
    }
}

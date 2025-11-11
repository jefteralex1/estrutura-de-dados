#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Para srand(time(NULL))
#include <string.h> // Para memcpy

#include "ordenacao.h"
#include "arvore.h"

#define TAM_VETOR 20
#define VALOR_MAX 500

// --- Funções Auxiliares (Geração do Vetor) ---

// Verifica se um valor já existe no vetor (até a posição 'limite')
int existe_no_vetor(int valor, int vetor[], int limite) {
    for (int i = 0; i < limite; i++) {
        if (vetor[i] == valor) {
            return 1; // Verdadeiro, já existe
        }
    }
    return 0; // Falso, não existe
}

// Gera 20 números aleatórios não repetidos entre 1 e 500
void gerar_vetor_aleatorio(int vetor[], int tam, int max_val) {
    for (int i = 0; i < tam; i++) {
        int num_aleatorio;
        do {
            // Gera número entre 1 e max_val (inclusive)
            num_aleatorio = (rand() % max_val) + 1;
        } while (existe_no_vetor(num_aleatorio, vetor, i)); // Verifica se já foi inserido
        
        vetor[i] = num_aleatorio;
    }
}

// Exibe um vetor com um título
void exibir_vetor(int vetor[], int tam, const char* titulo) {
    printf("%s\n", titulo);
    for (int i = 0; i < tam; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n\n");
}

// --- Função Principal ---

int main() {
    // Inicializa a semente do gerador aleatório
    srand(time(NULL));

    int vetor_original[TAM_VETOR] = {0}; // Inicializa com zeros
    int vetor_ordenado[TAM_VETOR];
    long n_comparacoes = 0;
    No* raiz_bst = NULL; // Importante inicializar a raiz como NULL

    // --- Saída 1: Nomes e Matrículas ---
    printf("=========================================\n");
    printf("      ATIVIDADE DE ESTRUTURA DE DADOS\n");
    printf("=========================================\n");
    printf("Integrantes do Grupo:\n");
    printf("* Álvaro Elias Gomes Santos Mendes Oliveira (202303759134)\n");
    printf("* Antonio Luís Alves de Oliveira (202404250717)\n");
    printf("* Jefter Alexandre Marcelino Alves Guimarães (202304472793)\n");
    printf("* João Vitor Rodrigues Rocha (202308604988)\n");
    printf("\nSoma das matriculas (digitos): 22 -> Modulo 3 = 1\n");
    printf("-----------------------------------------\n\n");

    // 1. Geração do Vetor
    gerar_vetor_aleatorio(vetor_original, TAM_VETOR, VALOR_MAX);
    
    // Guarda uma cópia para a ordenação (requisito 1)
    memcpy(vetor_ordenado, vetor_original, TAM_VETOR * sizeof(int));

    // --- Saída 2: Vetor Original ---
    exibir_vetor(vetor_original, TAM_VETOR, "--- 2. Vetor Original (Nao Ordenado) ---");

    // 3. Ordenação do Vetor
    // O ponteiro &n_comparacoes é passado para a função atualizar o valor
    selectionSort(vetor_ordenado, TAM_VETOR, &n_comparacoes);

    // --- Saída 3: Vetor Ordenado ---
    exibir_vetor(vetor_ordenado, TAM_VETOR, "--- 3. Vetor Ordenado ---");

    // --- Saída 4: Algoritmo e Comparações ---
    printf("--- 4. Analise da Ordenacao ---\n");
    printf("Algoritmo usado: Selection Sort (Resultado Modulo 1)\n");
    printf("Total de comparacoes: %ld\n\n", n_comparacoes);
    
    // 4. Construção da Árvore Binária de Busca (BST)
    // DEVE ser feita com os valores originais (não ordenados)
    for (int i = 0; i < TAM_VETOR; i++) {
        raiz_bst = inserir_no(raiz_bst, vetor_original[i]);
    }

    // --- Saída 5: Percurso da Árvore ---
    printf("--- 5. Percurso da Arvore (Em Ordem) ---\n");
    percurso_em_ordem(raiz_bst);
    printf("\n\n");

    // --- Saída 6: Altura da Árvore ---
    printf("--- 6. Altura da Arvore Binaria ---\n");
    printf("Altura: %d\n", altura(raiz_bst));
    printf("=========================================\n");

    // (Opcional: liberar memória da árvore - não exigido, mas boa prática)
    // implementar free_tree(raiz_bst);

    return 0;
}

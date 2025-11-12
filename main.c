// stdio.h (Standard Input/Output): Necessária para funções de entrada e saída, como o printf()
#include <stdio.h> 
// stdlib.h (Standard Library): Usada para alocação de memória (malloc/free), números aleatórios (rand/srand)
#include <stdlib.h> 
// time.h: Usada para obter a hora atual (time(NULL)), que serve para "embaralhar" os números aleatórios
#include <time.h> 
// string.h: Usada para a função memcpy(), que faz uma cópia rápida do vetor
#include <string.h> 

// "ordenacao.h" deve conter a função 'selectionSort()'
#include "ordenacao.h" 
// "arvore.h" contém as funções 'inserir_no', 'percurso_em_ordem', 'altura' e a struct 'No'
#include "arvore.h" 

// --- Bloco 2: Constantes (Definições globais) ---

// Define um "apelido" TAM_VETOR para o número 20. Facilita mudar o tamanho depois.
#define TAM_VETOR 20 
// Define o valor máximo que um número aleatório pode ter.
#define VALOR_MAX 500 

// --- Bloco 3: Funções Auxiliares (Para gerar o vetor) ---

// Esta função checa se um 'valor' já está presente no 'vetor'
// Ela só verifica até a posição 'limite' (quantos números já foram inseridos)
int existe_no_vetor(int valor, int vetor[], int limite) {
    // Loop 'for' que passa por cada item do vetor, de 0 até 'limite'
    for (int i = 0; i < limite; i++) {
        // Se o item atual (vetor[i]) for igual ao 'valor' que estamos procurando...
        if (vetor[i] == valor) {
            return 1; // ...retorna 1 (verdadeiro), indicando que o valor já existe.
        }
    }
    // Se o loop terminar sem encontrar o valor, retorna 0 (falso).
    return 0; 
}

// Esta função preenche o 'vetor' com 'tam' (20) números aleatórios
void gerar_vetor_aleatorio(int vetor[], int tam, int max_val) {
    // Loop que executa 'tam' (20) vezes, uma para cada posição do vetor
    for (int i = 0; i < tam; i++) {
        int num_aleatorio;
        // Este 'do-while' é um truque para garantir que não haja números repetidos
        do {
            // Gera um número aleatório. 
            // 'rand() % max_val' gera de 0 a 499. O '+ 1' ajusta para 1 a 500.
            num_aleatorio = (rand() % max_val) + 1; 
        // ...enquanto o número gerado JÁ EXISTIR no vetor (na parte que já preenchemos)...
        } while (existe_no_vetor(num_aleatorio, vetor, i)); // ...gera um novo número.
        
        // Quando sai do 'do-while', temos um número único. Ele é salvo no vetor.
        vetor[i] = num_aleatorio;
    }
}

// Função simples para imprimir qualquer vetor na tela
void exibir_vetor(int vetor[], int tam, const char* titulo) {
    // Imprime o título que foi passado como parâmetro
    printf("%s\n", titulo);
    // Loop 'for' que passa por todas as posições do vetor
    for (int i = 0; i < tam; i++) {
        // Imprime o número e um espaço
        printf("%d ", vetor[i]);
    }
    // Pula duas linhas no final para organizar a saída
    printf("\n\n");
}

// --- Bloco 4: Função Auxiliar (Para a Árvore) ---

// Função RECURSIVA para liberar a memória alocada pela árvore
// Isso é essencial em C para evitar "vazamento de memória" (memory leak)
void liberar_arvore(No* raiz) {
    // Condição de parada da recursão: se o nó for nulo, não faz nada.
    if (raiz == NULL) return;
    
    // 1. Libera o filho da esquerda
    liberar_arvore(raiz->esquerda); 
    // 2. Libera o filho da direita
    liberar_arvore(raiz->direita);
    // 3. Por último, libera o próprio nó (raiz)
    free(raiz);
}

// --- Bloco 5: Função Principal (Onde tudo acontece) ---

int main() {
    // "Semente" do gerador aleatório. 
    // Isso garante que, a cada execução do programa, os números aleatórios sejam DIFERENTES.
    srand(time(NULL)); 

    // Cria o vetor original, com 20 posições, inicializado com zeros.
    int vetor_original[TAM_VETOR] = {0};
    // Cria um segundo vetor, que será usado para a ordenação.
    int vetor_ordenado[TAM_VETOR];
    // Variável para contar quantas comparações o 'selectionSort' faz.
    long n_comparacoes = 0;
    // Ponteiro para o nó raiz da Árvore Binária de Busca. Começa como NULO (árvore vazia).
    No* raiz_bst = NULL;

    // --- Saída 1: Nomes e Matrículas (Parte do requisito do trabalho) ---
    printf("=========================================\n");
    printf("     ATIVIDADE DE ESTRUTURA DE DADOS\n");
    printf("=========================================\n");
    printf("Integrantes do Grupo:\n");
    printf("* Álvaro Elias Gomes Santos Mendes Oliveira (202303759134)\n");
    printf("* Antonio Luís Alves de Oliveira (202404250717)\n");
    printf("* Jefter Alexandre Marcelino Alves Guimarães (202304472793)\n");
    printf("* João Vitor Rodrigues Rocha (202308604988)\n");
    // Esta parte é a lógica do trabalho:
    // A soma (22) módulo 3 dá resto 1. Isso define o algoritmo e o percurso.
    printf("\nSoma das matriculas (digitos): 22 -> Modulo 3 = 1\n");
    printf("-----------------------------------------\n\n");

    // 1. Geração do Vetor
    // Chama a função para preencher o 'vetor_original' com 20 números únicos.
    gerar_vetor_aleatorio(vetor_original, TAM_VETOR, VALOR_MAX);
    
    // COPIA o vetor original para o 'vetor_ordenado'.
    // Isso é IMPORTANTE: queremos manter o original intacto para usar na árvore.
    // 'sizeof(int)' calcula quantos bytes um 'int' ocupa.
    memcpy(vetor_ordenado, vetor_original, TAM_VETOR * sizeof(int));

    // --- Saída 2: Vetor Original ---
    // Exibe o vetor antes de qualquer ordenação.
    exibir_vetor(vetor_original, TAM_VETOR, "--- 2. Vetor Original (Nao Ordenado) ---");

    // 3. Ordenação do Vetor (Selection Sort)
    // Chama a função que está em 'ordenacao.h'.
    // Ela ordena o 'vetor_ordenado' e usa o ponteiro '&n_comparacoes' para atualizar o contador.
    selectionSort(vetor_ordenado, TAM_VETOR, &n_comparacoes);

    // --- Saída 3: Vetor Ordenado ---
    // Mostra o resultado do 'selectionSort'.
    exibir_vetor(vetor_ordenado, TAM_VETOR, "--- 3. Vetor Ordenado ---");

    // --- Saída 4: Análise da Ordenação (Requisito do trabalho) ---
    printf("--- 4. Analise da Ordenacao ---\n");
    // Calcula o módulo 3 da soma das matrículas (que é 22).
    int modulo = 22 % 3; // modulo será 1
    
    // Este 'if/else' apenas IMPRIME o nome do algoritmo e percurso corretos.
    if (modulo == 0) printf("Algoritmo: Bubble Sort | Percurso: Pre-Ordem\n");
    // Como 22 % 3 == 1, esta é a linha que será impressa:
    else if (modulo == 1) printf("Algoritmo: Selection Sort | Percurso: Em-Ordem\n");
    else printf("Algoritmo: Insertion Sort | Percurso: Pos-Ordem\n");
    
    // Imprime o número de comparações que o 'selectionSort' fez.
    printf("Total de comparacoes: %ld\n\n", n_comparacoes);
    
    // 4. Construção da Árvore Binária de Busca (BST)
    // Loop 'for' que passa pelo VETOR ORIGINAL (não ordenado)
    for (int i = 0; i < TAM_VETOR; i++) {
        // Insere cada número, um por um, na árvore.
        // A função 'inserir_no' (de 'arvore.h') deve cuidar da lógica da BST.
        raiz_bst = inserir_no(raiz_bst, vetor_original[i]);
    }

    // --- Saída 5: Percurso da Árvore ---
    // Aqui está um ponto-chave:
    // O percurso "Em-Ordem" (In-Order) de uma Árvore Binária de BUSCA
    // sempre visita os nós em ordem crescente.
    printf("--- 5. Percurso da Arvore (Em Ordem) ---\n");
    // Chama a função 'percurso_em_ordem' (de 'arvore.h')
    percurso_em_ordem(raiz_bst); 
    // O resultado impresso aqui DEVE SER IDÊNTICO ao "Vetor Ordenado" da Saída 3.
    printf("\n\n");

    // --- Saída 6: Altura da Árvore ---
    printf("--- 6. Altura da Arvore Binaria ---\n");
    // Chama a função 'altura' (de 'arvore.h') para calcular a altura da árvore.
    printf("Altura: %d\n", altura(raiz_bst));
    printf("=========================================\n");

    // --- Liberação da Memória ---
    // Chama a função que criamos para limpar a árvore da memória.
    liberar_arvore(raiz_bst);
    // Boa prática: "zera" o ponteiro para evitar usá-lo acidentalmente.
    raiz_bst = NULL;

    // Indica que o programa terminou com sucesso.
    return 0; 
}

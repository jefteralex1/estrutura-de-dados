// Inclui o arquivo de cabeçalho (header) que "promete" que a função 
// 'selectionSort' vai existir.
#include "ordenacao.h" 
// Incluído para o 'printf', mas não é realmente usado aqui (um resquício)
#include <stdio.h> 

// --- Função 1: trocar (Função Auxiliar) ---

// Esta é uma função essencial para *qualquer* algoritmo de ordenação.
// Ela recebe o "endereço" (ponteiros) de duas variáveis inteiras.
// Usar ponteiros (int *a) é crucial, pois queremos alterar os valores
// ORIGINAIS no vetor, e não apenas cópias.
void trocar(int *a, int *b) {
    // 1. Cria uma "caixa" temporária para guardar o valor de 'a'
    int temp = *a; // '*a' significa "o valor que está no endereço 'a'"
    
    // 2. Coloca o valor de 'b' dentro de 'a'
    *a = *b; 
    
    // 3. Pega o valor original de 'a' (que salvamos em 'temp') e coloca em 'b'
    *b = temp;
    // Ao final, os valores nos endereços 'a' e 'b' foram trocados.
}

// --- Função 2: selectionSort (A Função Principal) ---

// Esta é a implementação do algoritmo Selection Sort.
// 'vetor[]': O vetor que queremos ordenar.
// 'tam': O tamanho (quantos elementos) do vetor.
// 'long *comparacoes': Um ponteiro para o contador. Usamos um ponteiro
//                      para que possamos alterar a variável 'n_comparacoes' 
//                      que foi criada lá no 'main.c'.
void selectionSort(int vetor[], int tam, long *comparacoes) {
    
    // Zera o contador. Importante, pois a variável no 'main' pode ter lixo.
    // (*comparacoes) significa "vá até o endereço 'comparacoes' e mude o valor lá"
    *comparacoes = 0; 
    
    // Declara as variáveis que usaremos nos loops
    int i, j, min_idx;

    // --- LOOP EXTERNO ---
    // Este loop passa por cada posição do vetor que precisa ser "preenchida".
    // 'i' é a posição que estamos tentando "fixar" com o valor correto.
    // Note que ele vai até 'tam - 1', porque quando 'i' for o penúltimo,
    // o último elemento automaticamente já estará no lugar certo.
    for (i = 0; i < tam - 1; i++) {
        
        // "A Hipótese": Assumimos, por enquanto, que o menor elemento
        // da parte "bagunçada" do vetor é o primeiro (posição 'i').
        min_idx = i; 
        
        // --- LOOP INTERNO ---
        // Este loop vai "escanear" o RESTO do vetor (da posição i+1 até o fim)
        // para *procurar* se existe algum elemento menor do que a nossa "hipótese".
        for (j = i + 1; j < tam; j++) {
            
            // CONTAGEM DA COMPARAÇÃO:
            // Cada vez que o 'if' vai rodar, estamos fazendo uma comparação.
            // Incrementamos o contador que está lá no 'main'.
            (*comparacoes)++; 
            
            // "A Descoberta": Comparamos o elemento 'j' com o nosso 'min_idx'
            if (vetor[j] < vetor[min_idx]) {
                // Se acharmos um número menor, atualizamos nossa "hipótese".
                // O novo "menor por enquanto" está na posição 'j'.
                min_idx = j; 
            }
        }
        
        // --- A TROCA ---
        // Depois que o Loop Interno (j) termina, 'min_idx'
        // guarda a posição do MENOR elemento de todo o resto do vetor.
        
        // Otimização: Só trocamos se o menor não for ele mesmo.
        // Se 'min_idx == i', o elemento já estava no lugar certo.
        if (min_idx != i) {
            // Traz o menor elemento (vetor[min_idx]) para a posição 'i',
            // e leva o elemento 'i' para o lugar onde o menor estava.
            trocar(&vetor[min_idx], &vetor[i]);
        }
        
        // Neste ponto, o elemento na posição 'i' está CORRETO e ORDENADO.
        // O loop 'i' avança, e repetimos o processo para i+1.
    }
}

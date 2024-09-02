/*
O código abaixo recebe do usuário elementos que são inseridos em uma matriz 3x3, em seguida, imprime a soma de sua diagonal principal.
- faça uma modificação para que seja possível dinamizar o tamanho da matriz (utilizar alocação dinâmica de memória usando malloc)
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i, j, n, soma = 0; // variáveis
    
    // obtem tamanho da matriz
    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);
    
    int **matriz = malloc(n * sizeof(int*)); // alocação de espaço de memória dinâmica
    
    // criação da matriz com alocação dinâmica
    for (i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int)); 
    }
    
    // inserção dos valores na matriz
    printf("Insira os elementos da matriz %dx%d:\n", n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]); // obtem valores da matriz 
            if (i == j) {
                soma += matriz[i][j]; // soma os valores da diagonal principal
            }
        }
    }
    
    printf("Soma dos elementos da diagonal principal: %d\n", soma);
    return 0;
}
/*
O código abaixo realiza a impressão do vetor na ordem inversa.
1 - comente o código
2 - faça uma modificação para que seja possível inserir um vetor de n elementos.
*/

#include <stdio.h>

int main() {
    int i, temp, n; // variáveis
    
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n); // obtem tamanho do vetor
    
    int vetor[n]; // cria um vetor de tamanho n
    
    // obtem os valores do vetor
    printf("Informe os valores do vetor: ");
    for(i = 0; i < n; i++){
        scanf("%d", &vetor[i]);
    }

    // inverte o vetor
    for (i = 0; i < (n/2); i++) {
        temp = vetor[i]; // variável temporária recebe o valor que está na posição i do vetor
        vetor[i] = vetor[(n-1) - i]; // vetor na posição i recebe o valor que está na posição (tamanho - i)
        vetor[(n-1) - i] = temp; // vetor na posição (tamanho - i) recebe o valor da variável temporáriaa
    }

    printf("Vetor invertido: ");
    
    // imprime os valores do vetor
    for (i = 0; i < n; i++) {
        printf("%d ", vetor[i]);
    }

    return 0;
}
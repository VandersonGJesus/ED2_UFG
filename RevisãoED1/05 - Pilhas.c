/*
O código abaixo apresenta a implementação de uma pilha e suas operações básicas.

1 - comente o código
2 - implemente uma função para verificar se a pilha está vazia.
3 - proponha uma função que possa fazer expansão dinâmica quando a capacidade máxima é atingida, em vez de simplesmente negar novas inserções na pilha.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 3  // capacidade inicial da pilha

int* pilha;         // ponteiro para o vetor que representa a pilha
int topo = -1;      // indice do topo da pilha -1 = pilha vazia
int capacidade = MAX_SIZE; // capacidade atual da pilha

// empilhar
void push(int elemento) {
    if (topo < capacidade - 1) {              // Verifica se ainda há espaço na pilha
        pilha[++topo] = elemento;             // Incrementa o topo e insere o elemento na posição correspondente
    } else {
        printf("Capacidade máxima atingida, aguarde a expanção a pilha...\n");
        capacidade *= 2;                      // dobra a capacidade da pilha
        pilha = realloc(pilha, capacidade * sizeof(int)); // expanção dinâmica de memória
        if (pilha != NULL) {                  
            pilha[++topo] = elemento;         // se a alocação for bem sucedida, então adiciona o elemento após a expansão
        } else {
            printf("Erro ao expandir a pilha!\n");
            exit(1);                          // finaliza o programa caso ocorra um erro
        }
    }
}

// remoção
int pop() {
    if (topo == -1) {                         // verifica se a pilha está vazia
        printf("Pilha vazia!\n");
        return -1;                            // etorna -1 indicando erro ao tentar remover de uma pilha vazia
    } else {
        return pilha[topo--];                 // tetorna o elemento do topo e decrementa o índice do topo
    }
}

// verifica o topo
int top() {
    if (topo == -1) {                         // verifica se a pilha está vazia
        printf("Pilha vazia!\n");
        return -1;                            // retorna -1 indicando que a pilha está vazia
    } else {
        return pilha[topo];                   // retorna o elemento no topo da pilha
    }
}

// imprime pilha
void imprimir() {
    printf("Conteúdo da pilha:\n");
    for (int i = topo; i >= 0; i--) {         // percorre a pilha do topo até o fundo
        printf("%d ", pilha[i]);              // imprime cada elemento
    }
    printf("\n");
}

int main() {
    pilha = (int*)malloc(capacidade * sizeof(int)); // aloção de memória dinâmica para a pilha
    if (pilha == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // inserção dos valores
    push(10);
    push(20);
    push(30);
    push(40);
    
    imprimir();
    
    printf("Elemento no topo: %d\n", top());   // imprime o elemento no topo da pilha
    printf("Elemento removido: %d\n", pop());  // remove e imprime o elemento no topo da pilha
    
    imprimir();             

    free(pilha);                               // libera a memória alocada para a pilha
    return 0;
}

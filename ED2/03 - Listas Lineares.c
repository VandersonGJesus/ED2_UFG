/*
O código abaixo apresenta a implementação de uma lista linear.

Para esse exemplo, faça:
- Implemente funções adicionais como buscar(int elemento) para encontrar a posição de um elemento na lista.
ou 
- Adicione métodos para inverter a lista, encontrar o máximo/mínimo, ou ordenar a lista.
*/

#include <stdio.h>
#define MAX_SIZE 10

int lista[MAX_SIZE];
int tamanho = 0;

void inserir(int elemento) {
    if (tamanho < MAX_SIZE) {
        lista[tamanho++] = elemento; // insere elemento se a lista não estiver cheia
    } else {
        printf("Lista cheia!\n");
    }
}

void remover(int index) {
    if (index < 0 || index >= tamanho) {
        printf("Índice inválido!\n");
    } else {
        for (int i = index; i < tamanho - 1; i++) {  // reorganiza lista após a remoção
            lista[i] = lista[i + 1]; 
        }
        tamanho--;
    }
}

void imprimir() {
    printf("Elementos da lista:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", lista[i]); // imprime cada elemento da lista
    }
    printf("\n");
}

void buscar(int elemento) {
    for (int i = 0; i < tamanho; i++) {
        if(lista[i] = elemento){
            printf("A posição do elemento eh: %d", i); // retorna a posição do elemento se for igual o item atual da lista
        } else {
            printf("Elemento não encontrado...");
        }
    }
}

void ordenarLista() {
    int temp, i, troca; // variáveis
    
    // efetua enquanto houver trocas de posição até a lista esteja totalmente ordenada
    do {
        troca = 0;
        for (i = 0; i < (tamanho - 1); i++) {
            if (lista[i] > lista[i + 1]) {
                temp = lista[i];
                lista[i] = lista[i + 1];
                lista[i + 1] = temp;
                troca = 1;
            }
        }
    } while (troca);
}

void inverterLista() {
    int temp, i;
    
    // inverte o vetor
    for (i = 0; i < (tamanho / 2); i++) {
        temp = lista[i]; // variável temporária recebe o valor que está na posição i do vetor
        lista[i] = lista[(tamanho - 1) - i]; // vetor na posição i recebe o valor que está na posição (tamanho - 1 - i)
        lista[(tamanho - 1) - i] = temp; // vetor na posição (tamanho - 1 - i) recebe o valor da variável temporária
    }
}

void minimo(){
    ordenarLista(); // ordena lista em ordem crescente: primeiro valor é o menor
    printf("O valor minimo da lista eh %d", lista[0]);
    printf("\n");
}

void maximo() {
    ordenarLista(); // ordena a lista em ordem crescente: último valor é o maior
    printf("O valor maximo da lista eh %d", lista[tamanho - 1]);
    printf("\n");
}

int main() {
    inserir(10);
    inserir(20);
    inserir(30);
    inserir(5);
    inserir(9);
    inserir(2);
    inserir(45);
    imprimir();
    remover(1); //remove o valor 20
    inverterLista();
    imprimir();
    ordenarLista();
    imprimir();
    minimo();
    maximo();
    return 0;
}
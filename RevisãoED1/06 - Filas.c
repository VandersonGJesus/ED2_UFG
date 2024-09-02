/*
O código abaixo apresenta a implementação de uma fila e suas operações básicas.

1 - comente o código
2 - implemente uma função para contar o número de elementos na fila.
3 - implemente uma função para limpar todos os elementos da fila, liberando memória apropriadamente.
*/

#include <stdio.h>
#include <stdlib.h>

// estrutura do nó
typedef struct Node {
    int data;          // dado do nó
    struct Node* next; // ponteiro para o próximo
} Node;

// estrutura da fila
typedef struct Queue {
    Node* front;       // ponteiro para o início
    Node* rear;        // ponteiro para o fim
} Queue; 

// cria fila
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));                 // alocação dinâmica de memória
    if (q == NULL) {
        printf("Falha na alocação de memória para a fila.\n");
        return NULL;                                          // se houver erro de alocação retorna nulo
    }
    q->front = q->rear = NULL;                                // inicializa fila vazia
    return q;
}

// enfileirar
void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));              // alocação dinâmica de memória
    if (newNode == NULL) {
        printf("Falha na alocação de memória para o novo nó.\n");
        return;                                               // finaliza, caso ocorra erro de alocação de memória
    }
    newNode->data = value;                                    // dado do nó recebe o valor passado no parâmetro da função
    newNode->next = NULL;                                     // próximo aponta para o vazio
    if (q->rear == NULL) { 
        q->front = q->rear = newNode;                         // se o ponteiro fim apontar para o nulo, então ambos ponteiros da estrutura apontará para o novo nó
    } else { 
        q->rear->next = newNode;                              // próximo ponteiro do fim recebe o novo nó
        q->rear = newNode;                                    // ponteiro fim recebe o novo nó
    }
}

// desenfileirar
int dequeue(Queue* q) {
    if (q->front == NULL) {                                 // verifica se a fila está vazia
        printf("Fila está vazia.\n");
        return -1;
    }
    Node* temp = q->front;                                  // nó temporário recebe o inicio da fila
    int data = temp->data;                                  // variável data recebe o valor do dado alocado no nó temporário
    q->front = q->front->next;                              // o ponteiro início recebe o próximo a ele
    if (q->front == NULL) {                                 
        q->rear = NULL;                                     // se o ponteiro início for nulo então o ponteiro fim também apontará para o nulo
    }
    free(temp);                                             // libera alocação de memória
    return data;                                            // retorna o valor removido da fila
}

// verifica se fila está vazia
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// imprime fila
void printQueue(Queue* q) {
    if (isEmpty(q)) {                               // verifica se a fila está vazia
        printf("A fila está vazia.\n");
        return;
    }
    Node* temp = q->front;                          // nó auxiliar recebe o início da fila
    printf("Elementos da fila: ");
    while (temp != NULL) {                          
        printf("%d ", temp->data);                  // enquanto o nó temporário não for nulo imprime o dado do nó
        temp = temp->next;                          // passa para o próximo nó
    }
    printf("\n");
}

// imprime o tamanho da fila
void queueLenght(Queue* q) {
    int count = 0;
    if (isEmpty(q)) {                               // verifica se a fila está vazia
        printf("A fila está vazia.\n");
        return;
    }
    Node* temp = q->front;                          // nó temporário para percorrer a fila
    while (temp != NULL) {
        count++;                                    // enquanto o nó temporário não for nulo incrementar uma unidade do contador
        temp = temp->next;                          // passa para o próximo nó
    }
    printf("O tamanho da fila eh: %d", count);      // imprime tamanho da fila
    printf("\n");
}

// limpa toda a fila
void cleanQueue(Queue *q) {
    if (isEmpty(q)) {                               // verifica se a fila está vazia
        printf("A fila está vazia.\n");
        return;
    }
    Node* current = q->front;                       // atual recebe o início da fila
    Node* nextOne;                                  // nó auxiliar para guardar o valor do próximo nó
    
    while (current != NULL) {   
        nextOne = current->next;                    // equanto o atual não for nulo, então nó auxiliar recebe o próximo
        free(current);                              // limpa espaço de memória alocado
        current = nextOne;                          // atual recebe o valor do nó auxiliar
    }
        
    printf("A fila foi limpa.\n");                  // validação de limpeza de dados
    
    // reinicia fila nula
    q->front = NULL;
    q->rear = NULL;
}

int main() {
    Queue* q = createQueue();       // cria fila
    
    // enfileira dados
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 56);
    enqueue(q, 75);
    enqueue(q, 78);
    enqueue(q, 100);
    
    printQueue(q);                  // imprime fila
    queueLenght(q);                 // imprime tamanho da fila
    
    // desenfileira valores 
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    printf("Desenfileirado: %d\n", dequeue(q));
    printQueue(q);
    
    queueLenght(q);                 // imprime tamanho da fila
    cleanQueue(q);                  // limpa todos os dados da fila

    return 0;
}
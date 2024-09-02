/*
O código apresenta uma lista duplamente ligada com operações básicas para inserir, deletar e imprimir.

1 - comente o código.
2 - Modifique a operação de inserção de dados, para que o usuário seja capaz de inserir valores para a lista.
3 - Faça uma operação de buscar por um valor específico, informado pelo usuário, onde o programa deve apresentar se o valor foi encontrado e, em caso afirmativo, exibir detalhes(vizinhos) do nó correspondente.
*/

#include <stdio.h>
#include <stdlib.h>

// estrutura do nó de uma lista duplamente encadeado
typedef struct Node {
    int data;               // armazena o dado do nó
    struct Node* next;      // ponteiro para o próximo
    struct Node* prev;      // ponteiro para o anterior
} Node;

// ponteiro para nó cabeça da lista
Node* head = NULL;

void insertFront(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node)); // alocação dinâmica de memória de um novo nó
    newNode->data = value;                       // atribui valor ao nó
    newNode->next = head;                        // ponteiro proximo do novo nó aponta para cabeça da lista
    newNode->prev = NULL;                        // ponteiro anterior do novo nó aponta para o NULL
    if (head != NULL)
        head->prev = newNode;                    // se o cabeça não for nula então o nó anterior recebe o novo nó
    head = newNode;                              // novo nó se torna a cabeça da lista
}

void deleteNode(Node* node) {
    if (node == head)
        head = node->next;              // se o nó for a cabeça então a cabeça passa a ser o próximo nó
    if (node->next != NULL)             
        node->next->prev = node->prev;  // se o próximo ponteiro não for nulo então o nó anterior do próximo aponta para o nó anterior do nó a ser apontado
    if (node->prev != NULL)
        node->prev->next = node->next;  // se o nó anterior não for nulo O próximo do nó anterior aponta para o próximo do nó a ser excluído
    free(node);                         // libera memória alocada
}

void printList() {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void searchValue(int value) {
    Node* temp = head;                                      // ponteiro auxiliar para percorrer a lista
    while (temp != NULL) {                                  // itera até ao final da lista
        if (temp->data == value) {                          // se o valor do nó atual é igual o valor imputado
            printf("Valor %d encontrado.\n", value);
            if (temp->prev != NULL)
                printf("Anterior: %d\n", temp->prev->data); // imprime o valor do nó anterior
            else
                printf("Anterior: NULL\n");                 // se não existir nó anterior retorna null
                
            if (temp->next != NULL)
                printf("Próximo: %d\n", temp->next->data);  // imprime o valor do próximo nó
            else
                printf("Próximo: NULL\n");                  // se não existir próximo nó retorna null
                
            return;                             // finaliza após encontrar o valor
        }
        temp = temp->next;                      // passa para o próximo nó
    }
    printf("Valor %d não encontrado.\n", value); // informa que o valor imputado não foi encontrado
}

int main() {
    int n, value, search;
    
    // verifica o tamanho da lista
    printf("Digite quantos valores deseja inserir na lista: ");
    scanf("%d", &n);
    
    // obtem os dados da lista
    for (int i = 0; i < n; i++) {
        printf("Insira o %dº valor: ", i+1);
        scanf("%d", &value);
        insertFront(value);
    }
    
    // imprime lista
    printList();
    
    // verifica o valor a ser buscado
    printf("Informe o valor a ser buscado: ");
    scanf("%d", &search);
    searchValue(search); // efetua a busca
    
    return 0;
}
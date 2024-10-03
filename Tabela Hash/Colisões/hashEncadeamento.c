/*
Tema do Estudo de Caso: Processamento de Dados de Sensores em um Sistema de Monitoramento IoT

Sempre que uma máquina já cadastrada houver uma mudança muito brusca em alguns dos seus dados,
há uma possibilidade de haver uma "suposta falha", senão ela estará "normal"

Tratamento de colisões por ENCADEAMENTO
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar o processamento de dados de uma máquina
typedef struct Maquina {
    int idMaquina;              // ID único da máquina
    float temperatura;          // Temperatura da máquina
    int pressao;                // Pressão da máquina
    int vibracao;               // Vibração da máquina
    float hora;                 // Hora do processamento
    char status[20];            // Status: "normal" ou "suposta falha"
    struct Maquina *proximo;    // Ponteiro para a próxima máquina (lista ligada)
} Maquina;

// Estrutura da Tabela Hash
typedef struct {
    Maquina *tabela[TAMANHO_HASH];  // Array de ponteiros para o início da lista ligada
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da máquina
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para criar uma nova máquina
Maquina *criar_maquina(int id, float temperatura, int pressao, int vibracao, float hora, const char *status) {
    Maquina *nova_maquina = (Maquina *)malloc(sizeof(Maquina));
    if (nova_maquina == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    nova_maquina->idMaquina = id;
    nova_maquina->temperatura = temperatura;
    nova_maquina->pressao = pressao;
    nova_maquina->vibracao = vibracao;
    nova_maquina->hora = hora;
    strcpy(nova_maquina->status, status);
    nova_maquina->proximo = NULL;
    return nova_maquina;
}

// Função para inserir uma máquina na tabela hash (usando listas ligadas para colisões)
void inserir(TabelaHash *tabela, Maquina *maquina) {
    int indice = funcao_hash(maquina->idMaquina);  // Calcula o índice baseado no ID
    maquina->proximo = tabela->tabela[indice];  // Insere no início da lista ligada
    tabela->tabela[indice] = maquina;
}

// Função para exibir todas as máquinas
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Maquina *atual = tabela->tabela[i];
        while (atual != NULL) {
            printf("Máquina ID: %d, Temperatura: %.2f, Pressão: %d, Vibração: %d, Hora: %.2f, Status: %s (Índice: %d)\n",
                   atual->idMaquina, atual->temperatura, atual->pressao, atual->vibracao, atual->hora, atual->status, i);
            atual = atual->proximo;  // Avança para a próxima máquina
        }
    }
}

// Função para buscar uma máquina na tabela hash pelo ID
Maquina *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    Maquina *atual = tabela->tabela[indice];
    
    while (atual != NULL) {
        if (atual->idMaquina == id) {
            return atual;  // Retorna a máquina se encontrada
        }
        atual = atual->proximo;  // Vai para a próxima máquina na lista ligada
    }
    return NULL;  // Retorna NULL se não for encontrada
}

// Função para excluir uma máquina na tabela hash pelo ID
void excluir(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para exclusão
    Maquina *atual = tabela->tabela[indice];
    Maquina *anterior = NULL;

    while (atual != NULL) {
        if (atual->idMaquina == id) {
            // Se o elemento a ser removido for o primeiro da lista
            if (anterior == NULL) {
                tabela->tabela[indice] = atual->proximo;  // Remove o primeiro elemento
            } else {
                anterior->proximo = atual->proximo;  // Remove o elemento no meio ou fim
            }
            free(atual);  // Libera a memória da máquina
            printf("Máquina com ID %d foi excluída.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Máquina com ID %d não encontrada para exclusão.\n", id);
}

// Função para contar o número total de máquinas na tabela hash
int contar_elementos(TabelaHash *tabela) {
    int total = 0;

    // Percorre todas as posições da tabela hash
    for (int i = 0; i < TAMANHO_HASH; i++) {
        Maquina *atual = tabela->tabela[i];

        // Percorre a lista ligada em cada posição
        while (atual != NULL) {
            total++;  // Incrementa o contador para cada máquina encontrada
            atual = atual->proximo;  // Vai para o próximo elemento na lista
        }
    }

    return total;
}

// Função para inserir 20 máquinas predefinidas na tabela hash
void inserir_dados_predefinidos(TabelaHash *tabela) {
    // Inserindo máquinas diretamente
    inserir(tabela, criar_maquina(101, 25.3, 33, 65, 123.5, "normal"));
    inserir(tabela, criar_maquina(102, 51.2, 32, 62, 126.4, "falha"));
    inserir(tabela, criar_maquina(103, 40.5, 30, 60, 124.3, "normal"));
    inserir(tabela, criar_maquina(104, 75.1, 36, 68, 127.6, "falha"));
    inserir(tabela, criar_maquina(105, 45.9, 29, 64, 120.1, "normal"));
    inserir(tabela, criar_maquina(106, 52.7, 31, 63, 119.7, "falha"));
    inserir(tabela, criar_maquina(107, 35.6, 34, 66, 122.8, "normal"));
    inserir(tabela, criar_maquina(108, 90.3, 37, 69, 130.9, "falha"));
    inserir(tabela, criar_maquina(109, 49.8, 35, 61, 123.2, "normal"));
    inserir(tabela, criar_maquina(110, 60.2, 30, 62, 125.5, "falha"));
    inserir(tabela, criar_maquina(111, 29.7, 33, 65, 118.6, "normal"));
    inserir(tabela, criar_maquina(112, 53.9, 32, 67, 124.7, "falha")); 
    inserir(tabela, criar_maquina(113, 22.8, 36, 64, 121.9, "normal"));
    inserir(tabela, criar_maquina(114, 48.5, 31, 60, 119.3, "normal"));
    inserir(tabela, criar_maquina(115, 70.4, 34, 63, 125.8, "falha"));
    inserir(tabela, criar_maquina(116, 33.2, 30, 62, 118.5, "normal"));
    inserir(tabela, criar_maquina(117, 81.6, 35, 66, 123.4, "falha"));
    inserir(tabela, criar_maquina(118, 47.9, 37, 68, 128.2, "normal"));
    inserir(tabela, criar_maquina(119, 55.0, 29, 61, 120.5, "falha"));
    inserir(tabela, criar_maquina(120, 28.4, 32, 64, 123.7, "normal"));



    printf("As máquinas foram inseridas com sucesso.\n");
}


// Função principal para demonstrar o uso da tabela hash com as máquinas
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Inserir os dados predefinidos na tabela hash
    inserir_dados_predefinidos(&tabela);
    
    // Exibir todas as máquinas inseridas
    printf("\nTodas as máquinas inseridas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);

    
    // Busca por uma transação específica
    printf("\nBuscar uma Máquina:\n");
    Maquina *m = buscar(&tabela, 102);
    if (m != NULL) {
        printf("Máquina ID: %d, Temperatura: %.2f, Pressão: %d, Vibração: %d, Hora: %f, Status: %s\n",
                  m->idMaquina, m->temperatura, m->pressao, m->vibracao, m->hora, m->status);
    } else {
        printf("Máquina não encontrada.\n");
    }
    
    
    // Excluir as transações selecionadas
    printf("\nMáquinas excluidas:\n");
    excluir(&tabela, 119);
    
    
    // Exibir todas as transações inseridas
    printf("\nMáquinas Atualizadas: %d\n", contar_elementos(&tabela));
    exibir_todas(&tabela);
    

    return 0;
}
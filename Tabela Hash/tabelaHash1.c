// Tema do Estudo de Caso: Processamento de Dados de Sensores em um Sistema deMonitoramento IoT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_HASH 10

// Estrutura para representar uma máquina financeira
typedef struct {
    int idMaquina;               // ID único da máquina
    float temperatura;          // Valor da máquina
    int pressao;
    int vibracao;
    float hora;
    char status[20];      // Status: "normal" ou "suspeita"
} Maquina;

// Estrutura da Tabela Hash
typedef struct {
    Maquina *tabela[TAMANHO_HASH];  // Array de ponteiros para armazenar máquinas

} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da máquina
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função para inserir uma máquina na tabela hash
void inserir(TabelaHash *tabela, Maquina *Maquina) {
    int indice = funcao_hash(Maquina->idMaquina);  // Calcula o índice baseado no ID
    tabela->tabela[indice] = Maquina;  // Insere a máquina na tabela
}

// Função para buscar uma máquina na tabela hash pelo ID
Maquina *buscar(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);  // Calcula o índice para busca
    return tabela->tabela[indice];  // Retorna a máquina encontrada
}

// Função para exibir máquinas suspeitas
void exibir_suspeitas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i] != NULL && strcmp(tabela->tabela[i]->status, "suspeita") == 0) {
            printf("Máquina ID: %d, Temperatura: %.2f, Pressão: %d, Vibração: %d, Hora: %f, Status: %s\n",
                   tabela->tabela[i]->idMaquina,
                   tabela->tabela[i]->temperatura,
                   tabela->tabela[i]->pressao,
                   tabela->tabela[i]->vibracao,
                   tabela->tabela[i]->hora,
                   tabela->tabela[i]->status
            );
        }
    }
}

// Função principal para demonstrar o uso da tabela hash com máquinas 
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela = {NULL};

    // Criação de algumas máquinas

    Maquina Maquina1 = {101, 25.3, 33, 65, 123.5, "normal"};
    Maquina Maquina2 = {102, 32.9, 32, 60, 124.6, "normal"};
    Maquina Maquina3 = {103, 35.5, 39, 70, 127.0, "normal"};
    Maquina Maquina4 = {101, 58.7, 56, 78, 127.8, "suspeita"};

    // Insere as máquinas na tabela hash
    inserir(&tabela, &Maquina1);
    inserir(&tabela, &Maquina2);
    inserir(&tabela, &Maquina3);
    inserir(&tabela, &Maquina4);

    // Busca por uma máquina específica
    Maquina *m = buscar(&tabela, 103);
    if (m != NULL) {
        printf("Máquina ID: %d, Temperatura: %.2f, Pressão: %d, Vibração: %d, Hora: %f, Status: %s\n",
               m->idMaquina, m->temperatura, m->pressao, m->vibracao, m->hora, m->status);
    } else {
        printf("Máquina não encontrada.\n");
    }

    // Exibir todas as máquinas suspeitas
    printf("\nMáquinas suspeitas:\n");
    exibir_suspeitas(&tabela);

    return 0;
}

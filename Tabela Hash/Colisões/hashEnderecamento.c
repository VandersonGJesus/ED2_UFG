/*
Tema do Estudo de Caso: Processamento de Dados de Sensores em um Sistema de Monitoramento IoT

Sempre que uma máquina já cadastrada houver uma mudança muito brusca em alguns dos seus dados,
há uma possibilidade de haver uma "suposta falha", senão ela estará "normal"

Tratamento de colisões por ENDEREÇAMENTO
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
    int ocupada;                // Flag para indicar se o slot está ocupado
} Maquina;

// Estrutura da Tabela Hash
typedef struct {
    Maquina tabela[TAMANHO_HASH];  // Array de máquinas
} TabelaHash;

// Função Hash: Retorna o índice baseado no ID da máquina
int funcao_hash(int id) {
    return id % TAMANHO_HASH;  // Usa módulo para determinar a posição na tabela
}

// Função hash para duplo hashing
int hash2(int id) {
    return 7 - (id % 7);  // Segunda função hash para duplo hashing
}

// Sondagem linear
int sondagem_linear(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + 1) % TAMANHO_HASH;  // Avança linearmente
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Sondagem quadrática
int sondagem_quadratica(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int i = 1;
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (funcao_hash(id) + i * i) % TAMANHO_HASH;  // Avança quadraticamente
        i++;
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Duplo hashing
int duplo_hashing(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);
    int step = hash2(id);
    int tentativas = 0;

    while (tabela->tabela[indice].ocupada && tentativas < TAMANHO_HASH) {
        indice = (indice + step) % TAMANHO_HASH;  // Usa duplo hashing
        tentativas++;
    }

    return (tentativas < TAMANHO_HASH) ? indice : -1;  // Retorna o índice ou -1 se a tabela estiver cheia
}

// Função para criar uma nova máquina
Maquina criar_maquina(int id, float temperatura, int pressao, int vibracao, float hora, const char *status) {
    Maquina nova_maquina;
    nova_maquina.idMaquina = id;
    nova_maquina.temperatura = temperatura;
    nova_maquina.pressao = pressao;
    nova_maquina.vibracao = vibracao;
    nova_maquina.hora = hora;
    strcpy(nova_maquina.status, status);
    nova_maquina.ocupada = 1;  // Marca o slot como ocupado
    return nova_maquina;
}

// Função para inserir uma máquina na tabela hash usando sondagem linear
void inserir_linear(TabelaHash *tabela, Maquina maquina) {
    int indice = funcao_hash(maquina.idMaquina);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = maquina;
    } else {
        // Se houver colisão, chama a sondagem linear
        int novo_indice = sondagem_linear(tabela, maquina.idMaquina);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = maquina;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma máquina na tabela hash usando sondagem quadrática
void inserir_quadratica(TabelaHash *tabela, Maquina maquina) {
    int indice = funcao_hash(maquina.idMaquina);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = maquina;
    } else {
        // Se houver colisão, chama a sondagem quadrática
        int novo_indice = sondagem_quadratica(tabela, maquina.idMaquina);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = maquina;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para inserir uma máquina na tabela hash usando duplo hashing
void inserir_duplo_hashing(TabelaHash *tabela, Maquina maquina) {
    int indice = funcao_hash(maquina.idMaquina);

    // Se não houver colisão, insere diretamente
    if (!tabela->tabela[indice].ocupada) {
        tabela->tabela[indice] = maquina;
    } else {
        // Se houver colisão, chama o duplo hashing
        int novo_indice = duplo_hashing(tabela, maquina.idMaquina);
        if (novo_indice != -1) {
            tabela->tabela[novo_indice] = maquina;
        } else {
            printf("Erro: Tabela hash está cheia.\n");
        }
    }
}

// Função para exibir todas as máquinas
void exibir_todas(TabelaHash *tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        if (tabela->tabela[i].ocupada) {
            printf("Máquina ID: %d, Temperatura: %.2f, Pressão: %d, Vibração: %d, Hora: %.2f, Status: %s (Índice: %d)\n",
                   tabela->tabela[i].idMaquina, tabela->tabela[i].temperatura, tabela->tabela[i].pressao,
                   tabela->tabela[i].vibracao, tabela->tabela[i].hora, tabela->tabela[i].status, i);
        }
    }
}

// Função de busca de uma máquina pelo ID
int buscar_maquina(TabelaHash *tabela, int id) {
    int indice = funcao_hash(id);

    // Verifica se a máquina está no índice direto
    if (tabela->tabela[indice].ocupada && tabela->tabela[indice].idMaquina == id) {
        return indice;
    }

    // Tenta encontrar a máquina usando sondagem linear
    int novo_indice = sondagem_linear(tabela, id);
    if (novo_indice != -1 && tabela->tabela[novo_indice].ocupada && tabela->tabela[novo_indice].idMaquina == id) {
        return novo_indice;
    }

    return -1; // Máquina não encontrada
}

// Função de exclusão de uma máquina pelo ID
void excluir_maquina(TabelaHash *tabela, int id) {
    int indice = buscar_maquina(tabela, id);
    if (indice != -1) {
        tabela->tabela[indice].ocupada = 0; // Marca o slot como desocupado
        printf("\nMáquina ID %d excluída.\n\n", id);
    } else {
        printf("\nMáquina ID %d não encontrada.\n\n", id);
    }
}

// Função principal para demonstrar o uso da tabela hash com sondagem
int main() {
    // Inicializa a tabela hash
    TabelaHash tabela_linear = {0};  // Todos os slots começam desocupados

    // Inserir máquinas na tabela hash usando sondagem linear
    printf("\nInserção com Sondagem Linear:\n");
    inserir_linear(&tabela_linear, criar_maquina(101, 25.3, 33, 65, 123.5, "normal"));
    inserir_linear(&tabela_linear, criar_maquina(102, 51.2, 32, 62, 126.4, "falha"));
    inserir_linear(&tabela_linear, criar_maquina(103, 40.5, 30, 60, 124.3, "normal"));
    inserir_linear(&tabela_linear, criar_maquina(104, 75.1, 36, 68, 127.6, "falha"));
    inserir_linear(&tabela_linear, criar_maquina(105, 45.9, 29, 64, 120.1, "normal"));

    exibir_todas(&tabela_linear);

    // Excluir uma máquina
    excluir_maquina(&tabela_linear, 102);

    // Exibir novamente após a exclusão
    exibir_todas(&tabela_linear);

    // Inserir máquinas na tabela hash usando sondagem quadrática
    printf("\nInserção com Sondagem Quadrática:\n");
    TabelaHash tabela_quadratica = {0};
    inserir_quadratica(&tabela_quadratica, criar_maquina(106, 52.7, 31, 63, 119.7, "falha"));
    inserir_quadratica(&tabela_quadratica, criar_maquina(107, 35.6, 34, 66, 122.8, "normal"));
    inserir_quadratica(&tabela_quadratica, criar_maquina(108, 90.3, 37, 69, 130.9, "falha"));
    inserir_quadratica(&tabela_quadratica, criar_maquina(109, 49.8, 35, 61, 123.2, "normal"));
    inserir_quadratica(&tabela_quadratica, criar_maquina(110, 60.2, 30, 62, 125.5, "falha"));

    exibir_todas(&tabela_quadratica);

    // Excluir uma máquina
    excluir_maquina(&tabela_quadratica, 110);

    // Exibir novamente após a exclusão
    exibir_todas(&tabela_quadratica);

    // Inserir máquinas na tabela hash usando duplo hashing
    printf("\nInserção com Duplo Hashing:\n");
    TabelaHash tabela_duplo = {0};
    inserir_duplo_hashing(&tabela_duplo, criar_maquina(111, 29.7, 33, 65, 118.6, "normal"));
    inserir_duplo_hashing(&tabela_duplo, criar_maquina(112, 53.9, 32, 67, 124.7, "falha"));
    inserir_duplo_hashing(&tabela_duplo, criar_maquina(113, 22.8, 36, 64, 121.9, "normal"));
    inserir_duplo_hashing(&tabela_duplo, criar_maquina(114, 48.5, 31, 60, 119.3, "normal"));
    inserir_duplo_hashing(&tabela_duplo, criar_maquina(115, 70.4, 34, 63, 125.8, "falha"));

    exibir_todas(&tabela_duplo);

    // Excluir uma máquina
    excluir_maquina(&tabela_duplo, 112);

    // Exibir novamente após a exclusão
    exibir_todas(&tabela_duplo);

    return 0;
}

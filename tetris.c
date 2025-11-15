#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Constante para o tamanho máximo da fila
#define TAMANHO_FILA 5

// Definição da struct Peca
// Armazena o tipo (nome) e o identificador único (id) da peça.
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L', etc.)
    int id;    // Identificador único da peça
} Peca;

// Estrutura da Fila Circular
Peca fila[TAMANHO_FILA];
int frente = 0; // Índice do primeiro elemento
int tras = -1;  // Índice do último elemento
int contador = 0; // Número atual de elementos na fila
int proximo_id = 0; // Contador global para garantir IDs únicos

void inicializarFila();
Peca gerarPeca();
void enqueue(Peca novaPeca);
Peca dequeue();
void exibirFila();
void menu();
void limparBuffer();

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. GERAR PEÇA
Peca gerarPeca() {
    Peca novaPeca;
    char tipos[] = {'I', 'O', 'T', 'L'}; // Tipos comuns de Tetris
    int numTipos = sizeof(tipos) / sizeof(tipos[0]);

    novaPeca.nome = tipos[rand() % numTipos];
    
    // Atribui o ID único e incrementa o contador global
    novaPeca.id = proximo_id++;

    return novaPeca;
}

// 2. INICIALIZAR FILA
void inicializarFila() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios
    printf("--- Inicializando Fila de Peças ---\n");
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(gerarPeca());
    }
    printf("[SUCESSO] Fila inicializada com %d peças.\n", TAMANHO_FILA);
    exibirFila();
}

// Insere uma nova peça no final da fila
void enqueue(Peca novaPeca) {
    if (contador == TAMANHO_FILA) {
        printf("[ERRO] Fila cheia! Não é possível inserir a peça [%c %d].\n", novaPeca.nome, novaPeca.id);
        return;
    }

    tras = (tras + 1) % TAMANHO_FILA;
    fila[tras] = novaPeca;
    contador++;
    printf("[INFO] Peça [%c %d] inserida no final da fila.\n", novaPeca.nome, novaPeca.id);
}

// Remove e retorna a peça da frente da fila.
Peca dequeue() {
    Peca pecaRemovida = {'\0', -1}; // Peça de erro/vazia

    if (contador == 0) {
        printf("[ERRO] Fila vazia! Nenhuma peça para jogar.\n");
        return pecaRemovida;
    }

    pecaRemovida = fila[frente];
    
    frente = (frente + 1) % TAMANHO_FILA;
    contador--;

    printf("[SUCESSO] Peça jogada (removida da frente): [%c %d].\n", pecaRemovida.nome, pecaRemovida.id);
    return pecaRemovida;
}

// 5. EXIBIR FILA
void exibirFila() {
    printf("\n--- Fila de Peças Futuras (%d/%d) ---\n", contador, TAMANHO_FILA);

    if (contador == 0) {
        printf("[VAZIA]\n");
        return;
    }

    printf("Fila: ");
    int i = frente;
    int elementos_exibidos = 0;

    while (elementos_exibidos < contador) {
        printf("[%c %d]", fila[i].nome, fila[i].id);
        
        // Adiciona seta se não for o último elemento
        if (elementos_exibidos < contador - 1) {
            printf(" -> ");
        }
        
        i = (i + 1) % TAMANHO_FILA;
        elementos_exibidos++;
    }
    printf("\n");
}

// FUNÇÃO PRINCIPAL E MENU
void menu() {
    printf("\n==================================================\n");
    printf("         TETRIS STACK - FILA DE PEÇAS          \n");
    printf("==================================================\n");
    printf("Opções de ação:\n");
    printf("--------------------------------------------------\n");
    printf("  1    | Jogar peça (dequeue)\n");
    printf("  2    | Inserir nova peça (enqueue)\n");
    printf("  0    | Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opção: ");
}

int main() {
    int opcao;
    
    inicializarFila();

    do {
        menu();
        if (scanf("%d", &opcao) != 1) {
            fprintf(stderr, "\n[ERRO] Entrada inválida. Tente novamente.\n");
            limparBuffer();
            opcao = -1; 
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: {
                dequeue();
                exibirFila();
                break;
            }
            case 2: {
                Peca nova = gerarPeca();
                enqueue(nova);
                exibirFila();
                break;
            }
            case 0: {
                printf("\nSaindo do Tetris Stack. Até a próxima!\n");
                break;
            }
            default:
                printf("\n[ERRO] Opção inválida. Por favor, escolha 1, 2 ou 0.\n");
        }
    } while (opcao != 0);

    return 0;
}
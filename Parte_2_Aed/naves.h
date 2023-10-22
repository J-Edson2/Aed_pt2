#ifndef NAVES_H_INCLUDED
#define NAVES_H_INCLUDED
#define MAX 100
#define RESOURCE_COUNT 3
#define HASH_SIZE 1000003

// Estrutura para representar uma nave
typedef struct {
    int prioridade; // Prioridade da nave
    int recursos[RESOURCE_COUNT]; // Recursos que a nave está carregando
} Nave;

// Estrutura para representar uma fila de prioridade
typedef struct {
    Nave dados[MAX]; // Array para armazenar as naves
    int frente; // Índice do início da fila
    int tras; // Índice do final da fila
} FilaPrioridade;

// Estrutura para representar um nó na tabela hash
typedef struct node {
    char chave[12]; // Chave do nó (representa uma permutação de recursos)
    struct node *proximo; // Ponteiro para o próximo nó na lista encadeada
} Node;

// funções que serão implementadas em naves.c

void inicializar(FilaPrioridade *fp);
int estaVazia(FilaPrioridade *fp);
int estaCheia(FilaPrioridade *fp);
void enfileirar(FilaPrioridade *fp, Nave nave);
Nave desenfileirar(FilaPrioridade *fp);
void imprimirNaves(FilaPrioridade *fp);

unsigned long hash(char *str);
Node* criarNode(char *chave);
void inserir(char *chave);
int buscar(char *chave);
#endif // NAVES_H_INCLUDED

#ifndef NAVES_H_INCLUDED
#define NAVES_H_INCLUDED
#define MAX 100
#define RESOURCE_COUNT 3
#define HASH_SIZE 1000003

// Estrutura para representar uma nave
typedef struct {
    int prioridade; // Prioridade da nave
    int recursos[RESOURCE_COUNT]; // Recursos que a nave est� carregando
} Nave;

// Estrutura para representar uma fila de prioridade
typedef struct {
    Nave dados[MAX]; // Array para armazenar as naves
    int frente; // �ndice do in�cio da fila
    int tras; // �ndice do final da fila
} FilaPrioridade;

// Estrutura para representar um n� na tabela hash
typedef struct node {
    char chave[12]; // Chave do n� (representa uma permuta��o de recursos)
    struct node *proximo; // Ponteiro para o pr�ximo n� na lista encadeada
} Node;

// fun��es que ser�o implementadas em naves.c

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

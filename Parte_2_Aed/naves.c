#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "naves.h"

Node* tabelaHash[HASH_SIZE];

// Função para calcular o valor hash de uma string
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return hash % HASH_SIZE;
}

// Função para criar um novo nó para a tabela hash
Node* criarNode(char *chave) {
    Node* novoNode = (Node*) malloc(sizeof(Node));
    strcpy(novoNode->chave, chave);
    novoNode->proximo = NULL;
    return novoNode;
}

// Função para inserir uma nova chave na tabela hash
void inserir(char *chave) {
    unsigned long indice = hash(chave);
    Node* novoNode = criarNode(chave);
    if(!tabelaHash[indice]) {
        tabelaHash[indice] = novoNode;
    } else {
        Node* temp = tabelaHash[indice];
        while(temp->proximo) {
            temp = temp->proximo;
        }
        temp->proximo = novoNode;
    }
}

// Função para buscar uma chave na tabela hash
int buscar(char *chave) {
    unsigned long indice = hash(chave);
    Node* temp = tabelaHash[indice];
    while(temp) {
        if(strcmp(temp->chave, chave) == 0) {
            return 0;
        }
        temp = temp->proximo;
    }
    return 1;
}

// Função para inicializar a fila de prioridade
void inicializar(FilaPrioridade *fp) {
	fp->frente = fp->tras = -1;
}

// Função para verificar se a fila de prioridade está vazia
int estaVazia(FilaPrioridade *fp) {
	return fp->frente == -1;
}

// Função para verificar se a fila de prioridade está cheia
int estaCheia(FilaPrioridade *fp) {
	return (fp->tras + 1) % MAX == fp->frente;
}

// Função para adicionar uma nave à fila de prioridade
void enfileirar(FilaPrioridade *fp, Nave nave) {
	if (estaCheia(fp)) {
		printf("Fila cheia\n");
		return;
	}

	if (estaVazia(fp)) {
		fp->frente = fp->tras = 0;
	} else {
		fp->tras = (fp->tras + 1) % MAX;
	}

	fp->dados[fp->tras] = nave;
}

// Função para remover a nave de maior prioridade da fila de prioridade
Nave desenfileirar(FilaPrioridade *fp) {
	if (estaVazia(fp)) {
		printf("Fila vazia\n");
		exit(1);
	}

	int indiceMaiorPrioridade = fp->frente;

	for(int i = fp->frente; i != (fp->tras + 1) % MAX; i = (i + 1) % MAX) {
		if(fp->dados[i].prioridade > fp->dados[indiceMaiorPrioridade].prioridade) {
			indiceMaiorPrioridade = i;
		}
	}

	Nave nave = fp->dados[indiceMaiorPrioridade];

	for(int i = indiceMaiorPrioridade; i != fp->tras; i = (i + 1) % MAX) {
		fp->dados[i] = fp->dados[(i + 1) % MAX];
	}

	if (fp->frente == fp->tras) {
		inicializar(fp);
	} else {
		fp->tras--;
		if(fp->tras < 0)
			fp->tras = MAX - 1;
	}

	return nave;
}

// Função para imprimir todas as naves na fila de prioridade
void imprimirNaves(FilaPrioridade *fp) {
	if(estaVazia(fp)) {
		printf("Nenhuma nave na fila\n");
		return;
	}

	printf("Naves:\n");
	for(int i = fp->frente; i != (fp->tras + 1) % MAX; i = (i + 1) % MAX) {
		printf("Nave com prioridade %d e recursos ", fp->dados[i].prioridade);
		for(int j = 0; j < RESOURCE_COUNT; j++) {
			printf("%d ", fp->dados[i].recursos[j]);
		}
		printf("\n");
	}
}

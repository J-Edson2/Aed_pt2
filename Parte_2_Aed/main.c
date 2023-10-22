#include <stdio.h>
#include "naves.h"
#include <locale.h>
int main() {
    setlocale(LC_ALL,"portuguese");
	FilaPrioridade fp;

	inicializar(&fp);

	int recursos[8][3] = {{4,2,5},{3,2,1},{1,2,3}, {1,3,2}, {2,1,3}, {2,3,1}, {3,1,2}, {3,2,1}};

	for(int i = 0; i < 8; i++) {
		Nave nave;
		nave.prioridade = i+1;
		for(int j = 0; j < RESOURCE_COUNT; j++) {
			nave.recursos[j] = recursos[i][j];
		}
		enfileirar(&fp, nave);
	}

	while(1){

		printf("1. Decolar nave\n2. Imprimir naves\n3. Sair\n");
		int opcao;
		scanf("%d", &opcao);

		switch(opcao){
			case 1:
			{
				Nave nave = desenfileirar(&fp);

				char chave[12];
				sprintf(chave, "%d%d%d", nave.recursos[0], nave.recursos[1], nave.recursos[2]);

				if(buscar(chave)){
					inserir(chave);
					printf("A expansão não vai ocorrer.\n");
				} else {
					printf("A expansão vai ocorrer!\n");
				}

				break;
			}
			case 2:
				imprimirNaves(&fp);
				break;
			case 3:
				return 0;
			default:
				printf("Opção inválida\n");
				break;
		}
	}

	return 0;
}

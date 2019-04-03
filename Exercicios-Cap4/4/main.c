#include "main.h"

int main(int argc, char **argv)
{
	int aux;
	if (argc != 2)
	{
		printf("ERRO: Parâmetros incorretos.\nUso correto: ./filacirc <tamanho_fila>\n");
		return EXIT_FAILURE;
	}

	FilaC fila;
	fila.tam = 0;
	sscanf(argv[1], "%d", &fila.tam);
	if (fila.tam <= 0)
	{
		printf("ERRO: Tamanho da fila deve ser maior ou igual a 1.\n");
		return EXIT_FAILURE;
	}
	
	fila.qtde = 0;
	fila.frente = -1; // fila vazia;
	fila.vet = (int*) malloc(sizeof(int) * fila.tam);

	while (scanf("%d", &aux) && aux != -1)
	{
		switch (aux)
		{
			case -2:
				printFilaC(&fila);
				break;
			default:
				pushFilaC(&fila, aux);
				break;
		}
	}

	return EXIT_SUCCESS;
}

void pushFilaC(FilaC *f, int n)
{
	f->frente++;
	f->frente %= f->tam; // wrap-around;
	f->qtde++; if (f->qtde > f->tam) {f->qtde = f->tam;}
	f->vet[f->frente] = n;
}

void printFilaC(FilaC *f)
{
	int cauda = f->frente - f->qtde + 1, i;
	cauda += (cauda < 0) ? f->tam : 0; // wrap-back-around;

	printf("Fila:");
	for (i = 0; i < f->qtde; i++)
		printf(" %d", f->vet[(cauda + i)%f->tam]);
	printf("\n");
}

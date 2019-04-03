#include <stdio.h>
#include "main.h"

int main(int argc, char **argv)
{
	int aux;
	Vetor *vet;
	novoVetor(&vet);
	while (scanf("%d", &aux) && aux != -1)
	{
		pushVetor(vet, aux);
	}

	double med = media(vet);
	double des = desvio(vet, med);
	printf("Media = %.2f\nDesvio padrao = %.2f\n", med, des);
	
	mataVetor(&vet);
	vet = NULL;

	return EXIT_SUCCESS;
}

double media(Vetor *vet)
{
	int i;
	double soma = 0;
	NoLista *aux = vet->inicio;
	for (i = 0; i < vet->quantidade; i++)
	{
		soma += aux->valor;
		aux = aux->proximo;
	}

	double media = soma/(double)vet->quantidade;

	return media;
}

double desvio(Vetor *vet, double media)
{
	int i;
	double desvio = 0;
	NoLista *aux = vet->inicio;
	for (i = 0; i < vet->quantidade; i++)
	{
		desvio += (aux->valor * aux->valor - 2 * aux->valor * media + media * media);
		aux = aux->proximo;
	}

	desvio /= vet->quantidade;
	desvio = sqrt(desvio);

	return desvio;
}

int novoVetor(Vetor **v)
{
	Vetor *vt = NULL;
	vt = (Vetor*) malloc(sizeof(Vetor));
	if (vt == NULL)
		return EXIT_FAILURE;
	vt->quantidade = 0;
	vt->inicio = NULL;

	*v = vt;

	return EXIT_SUCCESS;
}

int mataVetor(Vetor **v)
{
	NoLista *aux1 = NULL, *aux2 = NULL;
	aux1 = (*v)->inicio;
	if (aux1 != NULL)
	{
		while (aux1->proximo != NULL)
		{
			aux2 = aux1->proximo;
			aux1->proximo = NULL;
			free(aux1);
			aux1 = aux2;
			aux2 = NULL;
		}
		aux1->proximo = NULL;
		free(aux1);
		(*v)->inicio = NULL;
	}

	free(*v);
	*v = NULL;

	return EXIT_SUCCESS;
}

int pushVetor(Vetor *v, int num)
{
	NoLista *aux1 = NULL, *aux2 = NULL;
	aux1 = (NoLista*) malloc(sizeof(NoLista));
	if (aux1 == NULL)
		return EXIT_FAILURE;
	aux1->valor = num;
	aux1->proximo = NULL;

	v->quantidade++;

	if (v->inicio == NULL)
		v->inicio = aux1;
	else
	{
		aux2 = v->inicio;
		while (aux2->proximo != NULL)
			aux2 = aux2->proximo;
		
		aux2->proximo = aux1;
	}

	aux1 = aux2 = NULL;

	return EXIT_SUCCESS;
}

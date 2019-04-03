#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct noLista {
	int valor;
	struct noLista *proximo;
} NoLista;

typedef struct {
	int quantidade;
	NoLista *inicio;
} Vetor;

double media(Vetor *vet);
double desvio(Vetor *vet, double media);

int novoVetor(Vetor **v);
int mataVetor(Vetor **v);
int pushVetor(Vetor *v, int num);

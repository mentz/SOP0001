#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int tam;
	int qtde;
	int frente;
	int *vet;
} FilaC;

void pushFilaC(FilaC *f, int n);
void printFilaC(FilaC *f);

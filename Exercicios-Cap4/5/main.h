#include <stdio.h>
#include <stdlib.h>

typedef struct noFila {
	char *nome;
	struct noFila *proximo;
} NoFila;

typedef struct {
	NoFila *inicio;
} Fila;

typedef struct noFilaP {
	int prioridade;
	struct noFilaP *proximo;
} NoFilaP;


typedef struct {
	NoFilaP *inicio;
} FilaP;

int criaFilaP(FilaP *f);
int pushFilaP(FilaP *f, char *id, int prioridade);
int printMenigFilaP(FilaP *f, int prioridade);
int printIgualFilaP(FilaP *f, int prioridade);

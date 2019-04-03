#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 6

typedef struct Thread_arg {
	int num_thread;
	int inicio;
	int qtde;
};

pthread_barrier_t barrier;

int menor[NUM_THREADS], qtdePorThread;

void * findLowest(void* arg)
{
	long inicio = (long) arg;


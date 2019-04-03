#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MEM 1048768
#define NUM_THREADS 3

typedef int semaforo;

semaforo mutex;

void* thread(void* arg)
{
	long me = (long) arg;
	down(&mutex);
	come_memoria(MEM, me);
	up(&mutex);

	pthread_exit(0);
}

void come_memoria(long memkb, long id)
{
	int ** pp = malloc (sizeof(int*) * memkb), i;
	for (i = 0; i < memkb; i++)
	{
		pp[i] = NULL;
		pp[i] = malloc(1024);
		if (pp[i] == NULL)
		{
			puts("Erro feio na alocação! Fechando");
			exit(EXIT_FAILURE);
		}
	}

	printf("Alocado %ld KB - OK Thread %ld\n", memkb, id);

	for (i = 0; i < memkb; i++)
		free(pp[i]);
	
	free (pp);
}

int main(void)
{
	int i;
	pthread_t threads[NUM_THREADS];
	
	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&threads[i], NULL, thread, (void*) ((long) i));
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(&threads[i], NULL);
	}

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

void* PrintHello(void *arg)
{
	long tid = (long) arg;
	int * ret = malloc(sizeof(int));
	printf("Alo da thread %ld | %ld\n", tid, tid*tid);
	*ret = tid*tid;
	
	pthread_exit((void*) ret);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int * ret = NULL;
	int rc, i;
	long t, sum = 0;
	for (t = 0; t < NUM_THREADS; t++)
	{
		printf("main: criando thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);

		if (rc)
		{
			printf("ERRO - rc=%d\n", rc);
			exit(-1);
		}
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], (void**) &ret);
		sum += *ret;
	}
	
	printf("Soma dos retornos = %ld\n", sum);

	pthread_exit(NULL);
}

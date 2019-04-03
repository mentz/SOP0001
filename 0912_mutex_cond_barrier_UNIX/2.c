#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

pthread_cond_t cnd1, cnd2;
pthread_mutex_t mtx;
int n = 1;

void * X(void *arg)
{
	pthread_mutex_lock(&mtx);
	n = n * 16;
	pthread_cond_signal(&cnd1);
	pthread_mutex_unlock(&mtx);
}

void * Y(void *arg)
{
	pthread_mutex_lock(&mtx);
	if (n != 56)
		pthread_cond_wait(&cnd2, &mtx);

	n = n / 7;
	pthread_mutex_unlock(&mtx);
}

void * Z(void *arg)
{
	pthread_mutex_lock(&mtx);
	if (n != 16)
		pthread_cond_wait(&cnd1, &mtx);
	
	n = n + 40;
	pthread_cond_signal(&cnd2);
	pthread_mutex_unlock(&mtx);
}

int main(void)
{
	pthread_t t1, t2, t3;
	pthread_cond_init(&cnd1, NULL);
	pthread_cond_init(&cnd2, NULL);
	pthread_mutex_init(&mtx, NULL);
	pthread_create(&t1, NULL, (void*) X, NULL);
	pthread_create(&t2, NULL, (void*) Y, NULL);
	pthread_create(&t3, NULL, (void*) Z, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_cond_destroy(&cnd1);
	pthread_cond_destroy(&cnd2);
	pthread_mutex_destroy(&mtx);

	printf("n = %d\n", n);

	return 0;
}

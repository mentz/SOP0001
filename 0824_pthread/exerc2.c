#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define T_PAR 0
#define T_IMPAR 1

#define NELEM 2000000

int* vetor;

void* conta(void * tipo) 
{
    int i, *total = malloc(sizeof(int));
	long t = (long) tipo;
     
    for (i = 0; i < NELEM; i++) {
		if ((t == T_PAR) && ((vetor[i] % 2) == 0))
		   	(*total)++;
		else if ((t == T_IMPAR) && ((vetor[i] % 2) != 0))
			(*total)++;
    }

	pthread_exit((void*) total);
}

int main(int argc, char *argv[])
{
    int i, rc, rc_p, rc_i, *ret_p, *ret_i;
    struct timeval tv_ini, tv_fim;
    unsigned long time_diff, usec_diff, msec_diff;
	pthread_t th_p, th_i;
	
	vetor = malloc(sizeof(int) * NELEM);
    srandom(time(NULL));
    for (i = 0; i < NELEM; i++) {
	 	vetor[i] = (int)random();
    }

    /* marca o tempo de inicio */
    rc = gettimeofday(&tv_ini, NULL);
    if (rc != 0) {
	 	perror("erro em gettimeofday()");
	 	exit(1);
    }

    /* faz o processamento de interesse */
    rc_p = pthread_create(&th_p, NULL, conta, (void*) T_PAR);
    if (rc_p != 0)
	{
		printf("Erro: rc=%d\n", rc_p);
		exit(1);
	}
	
	rc_i = pthread_create(&th_i, NULL, conta, (void*) T_IMPAR);
	if (rc_i != 0)
	{
		printf("Erro: rc=%d\n", rc_i);
		exit(1);
	}
	
	rc_p = pthread_join(th_p, (void**) &ret_p);
	if (rc_p != 0)
	{
		printf("Erro: rc=%d\n", rc_p);
		exit(1);
	}

	rc_i = pthread_join(th_i, (void**) &ret_i);
	if (rc_i != 0)
	{
		printf("Erro: rc=%d\n", rc_i);
		exit(1);
	}

    /* marca o tempo de final */
    rc = gettimeofday(&tv_fim, NULL);
    if (rc != 0) {
	 	perror("erro em gettimeofday()");
	 	exit(1);
    }
    /* calcula a diferenca entre os tempos, em usec */
    time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) - 
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     
	/* converte para segundos + microsegundos (parte fracionária) */
    usec_diff = time_diff % 1000000L;
     
     /* converte para msec */
    msec_diff = time_diff / 1000;
     
    printf("O vetor tem %d numeros pares e %d numeros impares.\n", *ret_p,
	    *ret_i);
    printf("Tempo de execucao: %lu.%03lu mseg\n", msec_diff, usec_diff%1000);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

char * str = "HelloWorldThisIsATestPhrase";
int pos = 0, ssize;

void * prnt_str(void * arg)
{
	int i = 0, *m = (int*) arg;
	for ( ; i < *m; i++) 
		putc(str[(pos++)%ssize], stdout);

	return 0;
}

int main(int argc, char ** argv)
{
	int qt, i, *m, *ths = NULL;
	ssize = strlen(str);
	*m = ssize/qt;
	sscanf(argv[1], "%d", &qt);

	ths = malloc(sizeof(int) * qt);
	pthread_t * th = malloc(sizeof(pthread_t) * qt);

	for (i = 0; i < qt; i++)
		pthread_create(&th[i], NULL, prnt_str, (void*) m);

	for (i = 0; i < qt; i++)
		pthread_join(th[i], (void*) &ths[i]);

	return 0;
}

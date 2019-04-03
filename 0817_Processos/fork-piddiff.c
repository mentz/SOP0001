#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	pid_t f, last;

	f = last = getpid();

	printf("Processo principal (PID=%u)\n", last);

	do
	{
		last = f;
		f = fork();
		if (f == 0)
			exit(0);
	} while (last == f - 1);

	printf("Diferença: %u\n", f - last);

	return 0;
}

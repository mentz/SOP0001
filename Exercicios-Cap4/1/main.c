#include <stdio.h>

int main(int argc, char ** argv)
{
	int n = argc;
	printf("Programa: %s\nParâmetros:\n", argv[0]);

	while (n-- > 1)
	{
		printf("%s\n", argv[n]);
	}

	return 0;
}
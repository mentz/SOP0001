#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Erro: Argumentos faltantes.\n");
		exit(EXIT_FAILURE);
	}

	char *buff;
	int length, perms, readlen, buffersize;

	int f1, f2; // File descriptors
	struct stat f1stat, f2stat;

	if (stat(argv[1], &f1stat) == -1)
	{
		perror("Erro: stat(argv[1])");
		exit(EXIT_FAILURE);
	}

	f1 = open(argv[1], O_RDONLY);
	
	if (f1 == -1)
	{
		perror("Erro: open(f1)");
		exit(EXIT_FAILURE);
	}

	f2 = open(argv[2], O_RDONLY);
	if (f2 != -1)
	{
		printf("Erro: Arquivo de destino já existe.\n");
		close(f2);
		exit(EXIT_FAILURE);
	}
	close(f2);

	length = f1stat.st_size;
	buffersize = f1stat.st_blksize;
	perms = f1stat.st_mode;

	buff = malloc(sizeof(char) * buffersize);
	
	f2 = open(argv[2], O_WRONLY | O_CREAT, perms);

	if (f2 == -1)
	{
		perror("Erro: open(f2)");
		exit(EXIT_FAILURE);
	}

	while (length > 0)
	{
		readlen = ((length >= buffersize) ? buffersize : length);
		if (read(f1, buff, readlen) != readlen)
		{
			perror("Erro: read(f1)");
			exit(EXIT_FAILURE);
		}

		if (write(f2, buff, readlen) != readlen)
		{
			perror("Erro: write(f2)");
			exit(EXIT_FAILURE);
		}

		length -= readlen;
	}

	if (close(f1) == -1)
	{
		perror("Erro: close(f1): ");
		exit(EXIT_FAILURE);
	}

	if (close(f2) == -1)
	{
		perror("Erro: close(f2): ");
		exit(EXIT_FAILURE);
	}

	return 0;
}

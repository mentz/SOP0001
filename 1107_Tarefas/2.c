#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv)
{
	char path[PATH_MAX];
	DIR *dir = NULL;
	struct dirent *node;

	if (argc < 2)
		strcpy(path, "./");
	else
		strcpy(path, argv[1]);

	dir = opendir(path);
	if (dir == NULL)
	{
		perror("Erro: opendir(path)");
		exit(EXIT_FAILURE);
	}

	while ((node = readdir(dir)) != NULL)
	{
		switch (node->d_type)
		{
			case DT_DIR:
				printf("D ");
				break;
			
			case DT_REG:
				printf("A ");
				break;

			default:
				printf("O ");
				break;
		}
		printf("%s\n", node->d_name);
	}

	if (closedir(dir) == -1)
	{
		perror("Erro: closedir(dir)");
		exit(EXIT_FAILURE);
	}

	return 0;
}

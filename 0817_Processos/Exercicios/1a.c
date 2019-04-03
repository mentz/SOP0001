#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t child_pid;

	child_pid = fork();

	if (child_pid != 0)
	{
		printf("A\n");
		child_pid = fork();
		if (child_pid != 0)
		{
			child_pid = fork();
			if (child_pid != 0) {}
			else
				printf("D\n");
		}
		else
			printf("C\n");
	}
	else
		printf("B\n");
	
	return 0;
}

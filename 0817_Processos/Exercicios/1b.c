#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t ch_p;

	ch_p = fork();

	if (ch_p != 0)
	{
		printf("A\n");
		fflush(stdout);
	}
	else
	{
		printf("B\n");
		fflush(stdout);
		ch_p = fork();

		if (ch_p == 0)
		{
			printf("C\n");
			fflush(stdout);
			ch_p = fork();

			if (ch_p == 0)
			{
				printf("D\n");
				fflush(stdout);
			}
		}
	}

	return 0;
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	pid_t f1, f2, f3, f4;

	f1 = fork();

	if (f1 != 0)
	{
		printf("A\n");

		f2 = fork();

		if (f2 != 0)
		{
			printf("
	else


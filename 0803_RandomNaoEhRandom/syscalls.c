#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int v1[1000], v2[1000];

int main(void)
{
	FILE *fp;
	int i, n;
	unsigned long total;
	char *buf;
	
	sleep(3);
	for (i = 0; i < 1000; i++) {
		v1[i] = random();
		v2[i] = random();
	}
	total = 0;
	for (i = 0; i < 1000; i++)
		total += v1[i] + v2[i];
	n = printf("Total=%lu\n", total);
	fflush(stdout);

	sleep(3);

	buf = (char *)malloc(1024);
	fp = fopen("/etc/issue", "r");
	if (fp != NULL && buf != NULL) {
		n = fread(buf, 1, 1024, fp);
		printf("n=%d\n", n);
		fclose(fp);
		free(buf);
	}

	sleep(3);
	return 0;
}

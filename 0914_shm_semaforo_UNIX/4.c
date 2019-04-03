#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>


#define MAX 2000

sem_t *sem;
int *ptr;

void up() {
	int i, temp;
	printf("Thread up()   - %p\n", ptr);
	for (i = 0; i < MAX; i++) {
		sem_wait(sem);
		temp = *ptr;
		temp++;
		*ptr = temp;
		sem_post(sem);
	}
}

void down() {
	int i, temp;
	printf("Thread down() - %p\n", ptr);
	for (i = 0; i < MAX; i++) {
		sem_wait(sem);
		temp = *ptr;
		temp--;
		*ptr = temp;
		sem_post(sem);
	}
}

int main(void) {
	
	// INICIO Alocar shared_mem, inteiro para contagem.
	int rc, fd;
	fd = shm_open("/smh_up_down", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		puts("Error in smh_open()");
		return 1;
	}
	rc = ftruncate(fd, sizeof(int));
	if (rc == -1)
	{
		puts("Error in ftruncate()");
		return 2;
	}
	ptr = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (ptr == MAP_FAILED)
	{
		puts("Error in mmap()");
		return 3;
	}
	// FIM Alocar shared_mem.


	// INICIO criar semáforo.
	sem = sem_open("/sem_up_down", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (sem == SEM_FAILED)
	{
		puts("Error in sem_open()");
		return 4;
	}
	// FIM criar semáforo.


	*ptr = 0;


	// INICIO fork, um processo roda up() e outro down().
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		up();
		return 0;
	}
	else
	{
		down();
		waitpid(pid, NULL, 0);
	}
	// FIM fork.


	printf("n = %d\n", *ptr);


	// INICIO desalocar shared_mem, somente o pai faz isso.
	if (munmap(ptr, sizeof(int)) == -1)
	{
		puts("Error in mummap()");
		return 5;
	}
	if (shm_unlink("/smh_up_down") == -1)
	{
		puts("Error in smh_unlink()");
		return 6;
	}
	// FIM desalocar shared_mem.
	

	// INICIO destruir semáforo.
	if (sem_close(sem) == -1)
	{
		puts("Error in sem_close()");
		return 7;
	}
	if (sem_unlink("/sem_up_down") == -1)
	{
		puts("Error in sem_unlink()");
		return 8;
	}
	// FIM destruir semáforo.


	return 0;
}

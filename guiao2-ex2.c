#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main ()
{
	pid_t pid;

	printf("current pid: %d\n", getpid());

	if ((pid = fork()) == 0) {
		// codigo processo filho
		printf("Filho -PID=%d --- PID Pai=%d\n", getpid(), getppid());
	} else { 
		// codigo processo pai
		printf("Pai -PID=%d --- PID Pai=%d --- PID filho%d\n", getpid(), getppid(), pid);
	}

	printf("Ola mundo!\n");
	return 0;
}

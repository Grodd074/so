#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define NUM_CHILDREN 4

int main ()
{
	int status;
	(*p) = 0;

	for (int i = 0; i < NUM_CHILDREN; i++) {
		pid_t pid = fork();
		if (pid < 0) {
			perror ("fork failed");
			exit(1);
		}
		else if (pid == 0) {
			// Child now exec's
			printf ("pid %d -- i=%d\n", getpid(), i);
			// Do interesting stuff
			sleep(3);
			_exit(i);
		}
	}

	// Parent
	printf("Parent is now doing something amazing ...\n");

	// Parent waits for child
	for (int i = 0; i < NUM_CHILDREN; i++) {
		pid_t terminated_pid = wait(&status);
		printf("[pai] process %d exited. exit code %d\n", terminated_pid, WEXITSTATUS(status));
	}

	return 0;
}

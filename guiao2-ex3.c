#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main ()
{
	pid_t pid;
	int status;

	for (int i=0; i<10; i++) {
		if ((pid = fork()) == 0) {
			printf ("pid %d -- i=%d\n", getpid(), i);
			_exit(i);
		} else {
			pid_t terminated_pid = wait(&status);
			printf("[pai] process %d exited. exit code %d\n", terminated_pid, WEXITSTATUS(status));
		}
	}

	return 0;
}

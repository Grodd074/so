#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main (int argc, char** argv)
{
	int exec_ret, wait_ret, status;

	pid_t fork_ret = fork();
	if (fork_ret == 0) {
		// Codigo filho
		argv[0] = "alooo mundo";
		exec_ret = execvp("./ex3.out", argv);

		printf("blabla\n");
		perror("reached return");

		_exit (exec_ret);
	}
	else {

		printf("Sou o pai %d\n", getpid());
		wait_ret = wait(&status);

		if(WIFEXITED(status)) {
			printf("O filho retornou %d\n", WEXITSTATUS(status));
		} else {
			printf("O filho nao terminou\n");
		}
	}

	return 0;
}

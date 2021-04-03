#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main (int argc, char** argv)
{
	int fork_ret, exec_ret, wait_ret, status;

	char * exec_args[] = {"/bin/ls", "-l", "-u", NULL};

	fork_ret = fork();

	if (fork_ret == 0) {
		printf("Sou o filho %d\n", getpid());

		exec_ret = execv("/bin/ls", exec_args);

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

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main (int argc, char** argv)
{
	int exec_ret, wait_ret, status;

	for (int i = 1; i < argc; i++) {
		pid_t fork_ret = fork();
		if (fork_ret == 0) {
			// Codigo filho
			exec_ret = execlp(argv[i], argv[i], NULL); // Unico argumento nome do proprio programa

			perror("reach return");
			_exit (exec_ret);
		}
	}

	// Codigo do pai

	printf("Sou o pai %d\n", getpid());

	// Esperar por todos os filhos
	for (int i = 1; i < argc; i++) {
		wait_ret = wait(&status);
		if(WIFEXITED(status)) {
			printf("O filho retornou %d\n", WEXITSTATUS(status));
		} else {
			printf("O filho nao terminou\n");
		}

	}

	return 0;
}

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int mysystem(char * comando) {
	int exec_ret, wait_ret, status;
	pid_t fork_ret = fork();
	if (fork_ret == 0) {
		// Codigo filho
		// execv("ls", {"ls",...,NULL});
		exec_ret = execlp(comando, comando, NULL); // Unico argumento nome do proprio programa

		perror("reach return");
		_exit (exec_ret);
	} else {
		// Codigo do pai
		wait_ret = wait(&status);
		if(WIFEXITED(status)) {
			printf("O filho retornou %d\n", WEXITSTATUS(status));
		} else {
			printf("O filho nao terminou\n");
		}
	}

}

int main (int argc, char** argv)
{
//	mysystem("ls -l");

	mysystem("ps");

	mysystem("ls");

	return 0;
}

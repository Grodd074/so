#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ARGS 128
#define MAX_ACTIVE_JOBS 16

int jobs[MAX_ACTIVE_JOBS];
int active_jobs = 0;

int mysystem(char * comando) {
	int exec_ret, wait_ret, status;

	char* argv [MAX_ARGS];
	char * piece = strtok(comando, " ");
	int i = 0;
	while (piece != NULL) {
		argv[i] = piece;
		piece = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;

	// Test
/*	printf("|args: ");
	int j = 0;
	while (j < i) {
		printf("%s", argv[j]);
		j++;
	}
	printf("|\n");
*/


	// Background
	if ( strcmp(argv[i - 1], "&") == 0 ) {
		// Deletes '&' as argument
		argv[i - 1] = NULL;
		pid_t pid = fork();
		if ( pid == 0 ) {
			exec_ret = execvp(argv[0], argv); // execv("ls", {"ls",...,NULL});
			perror ("reach return");
			_exit (exec_ret);
		} else {
			//wait_ret = wait(&status);
			active_jobs += 1;
			printf("[%d] %d\n", active_jobs, pid);
		}
	} else { // Foreground
		if (!fork()) {
			exec_ret = execvp(argv[0], argv); // Unico argumento nome do proprio programa
			perror("reach return");
			_exit (exec_ret);
		} else {
			wait_ret = wait(&status);
			if(WIFEXITED(status)) {
				printf("O filho retornou %d\n", WEXITSTATUS(status));
			} else {
				printf("O filho nao terminou\n");
			}
		}

	}
}

int main (int argc, char** argv)
{
	printf("groddShell=> ");
	char buf[1024];
	while( fgets(buf, 1024, stdin) ) {

		buf[strlen(buf) - 1] = '\0'; // removes \n
		if ( strcmp(buf, "quit") == 0 )
			break;
		mysystem(buf);
		printf("groddShell=> ");

	};

	return 0;
}

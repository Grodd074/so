#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define NUM_CHILDREN 4

int main (int argc, char * argv[])
{
	if (argc < 2) {
		printf("Usage: program <needle>\n");
		exit(-1);
	}
	pid_t pid;
	int needle = atoi(argv[1]);
	int rows = 10;
	int cols = 10000;
	int rand_max = 10000;
	int status;
	int ** matrix;
	int pids[rows];

	// Allocate and populate matrix with random numbers
	printf("Generating numbers from 0 to %d...", rand_max);
	matrix = (int **) malloc(sizeof(int *) * rows);
	for (int i=0; i < rows; i++) {
		matrix[i] = (int *) malloc(sizeof(sizeof(int)) * cols);
		for (int j=0; j < cols; j++) {
			matrix[i][j] = rand() % rand_max;
		}
	}
	printf("Done.\n");

	for (int i = 0; i < rows; i++) {
		if ( (pid = fork()) == 0) {
			printf("[pid %d] row: %d\n", getpid(), i);

			// Start searching for the given number in row #i
			for (int j=0; j < cols; j++) {
				if (matrix[i][j] == needle)
					_exit(i);
			}
			_exit(-1);
		} else
			pids[i] = pid;

	for (int i = 0; i < rows; i++) {
		// Vai esperar primeiro pelo filho que criou primeiro
		pid_t terminated_pid = waitpid(pids[i], &status, 0);

		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) < 255) // Quando o filho retorna -1 o pai recebe 255
				printf("[pai] process %d exited. found number at row: %d\n", terminated_pid, WEXITSTATUS(status));
			else
				printf("[pai] process %d exited. nothing found\n", terminated_pid);
		} else {
			printf("[pai] process %d exited. something went wrong %d\n", terminated_pid);
		}
	}
	return 0;
}

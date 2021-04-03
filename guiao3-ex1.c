#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>

int main (int argc, char** argv)
{
	int ret;
	char * exec_args[] = {"/bin/ls", "-l", "-u", NULL};

	//ret = execl ("/bin/ls", "/bin/ls", NULL);

	// ret = execlp("ls", "/bin/ls", "-l", NULL);

	// so da return quando da asneira ou tentamos executar um programa que nao existe ex: "/bin/lsdsld"
	ret = execv("/bin/ls", exec_args);

	//ret = execvp ("ls", exec_args);

	printf("ola %d\n", ret);
	perror("reached return");

	return 0;
}

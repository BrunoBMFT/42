#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void	child_process(int *fd)
{
	close(fd[0]); //close unused end (the reading end) of the pipe
	write(fd[1], "sent from child", 15);  
	close(fd[1]); //close after writing into the pipe
	exit(EXIT_SUCCESS);  
}

void	parent_process(int *fd)
{
	close(fd[1]); //close unused end (the writing end) of the pipe
	char  str[15];
	read(fd[0], str, 15);
	printf("Parent received: %s\n", str);
	close(fd[0]); //close after reading from the pipe
	wait(NULL);
}

int main(void)
{
	pid_t   pid;
	int fd[2];

	pipe(fd);
	//when execve is used, the process forgets the rest of the program
	pid = fork();//forked so when execve runs, it saves the prev process
	if (pid < 0) 
	{
		fprintf(stderr, "Fork2 failed.\n");
		return 1;
	}
	else if (pid == 0)
		child_process(fd);
	else
		parent_process(fd);
	return EXIT_SUCCESS;
}
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int fd[2];
	//fd[0] = read
	//fd[1] = write
	//basically 2 ends of a pipe
	if (pipe(fd) == -1)
	{
		printf("error");
		return 1;
	}
	int id = fork();
	if (id == 0)
	{
		printf("in child process\n");
		close(fd[0]);//closes read since only write will be used
		int x;
		printf("input: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);//closes the write since it doesnt need to be used anymore
	}
	else//runs first
	{
		printf("in parent process\n");
		close(fd[1]);//closes write
		int y;
		read(fd[0], &y, sizeof(int));
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
}
#include "../includes/pipex.h"

void    callexecve()
{
    char *const args[] = { "ls", NULL };
    char *const envp[] = { NULL };

    execve("/usr/bin/ls", args, envp);
    perror("execve");
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

void	child_process(int *fd, char **av, char **envp)
{
	close(fd[0]);//close unused path
	dup2(fd[1], 1);
	printf("in child\n");
	callexecve();
	close(fd[1]);
	exit(EXIT_SUCCESS);//dont know if correct
}

void	parent_process(int *fd, char **av, char **envp)
{
	close(fd[1]);//close unused path
	dup2(fd[0], 0);
	close(fd[0]);
	wait(NULL);//use waitpid?
}

int main(int ac, char **av, char **envp)
{
	int fd[2];
	pid_t pid;//process id
//	if (ac == 5)
//	{
		pipe(fd);//make fd be pipe (have 2 ends)
		pid = fork();
		if (pid < 0)//error
			return (ft_putendl("error"), 1);
		else if (pid == 0)//here usually separate so i can visualize better during testing (1 function for parent and 1 for child)
		{
			printf("child, also parent\n");
			callexecve();
		}
		else if (pid > 1)
		{
			printf("parent\n");
			waitpid(pid, NULL, 0);
			printf("back to parent\n");
		}
		/*else if (pid == 0)//child
			child_process(fd, av, envp);
		else if (pid > 1)//parent
			parent_process(fd, av, envp);*/
		return (0);
//	}

}
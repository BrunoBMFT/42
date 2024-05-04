#include "../includes/pipex.h"
// ./pipex infile "cat" "wc" outfile
// < infile cat | wc > outfile
// check path
void    execute(char *arg)
{
    char *const envp[] = { NULL };
	char **com = ft_split(arg, ' ');
	printf("%s\n", com[0]);
	execve("/home/bruno/42/pipex/infile", com, envp);
	perror("execve");// dont use perror 
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

void	child_process(int *fd, char **av, char **envp)
{
	close(fd[0]);//close unused path
//	dup2(fd[1], 1);
	printf("in child\n");//printf dont work if dup2 comes before because stdout becomes fd[1]
	execute(av[2]);
	close(fd[1]);
	exit(EXIT_SUCCESS);//dont know if correct
}

void	parent_process(int *fd, char **av, char **envp)
{
	printf("parent\n");
	close(fd[1]);//close unused path
//	dup2(fd[0], 0);
	execute(av[3]);
	close(fd[0]);
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
		else if (pid == 0)//child
			child_process(fd, av, envp);
		waitpid(fd[0], NULL, 0);
		parent_process(fd, av, envp);
		return (0);
//	}

}
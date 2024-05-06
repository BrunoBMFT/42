#include "../includes/pipex.h"
// ./pipex infile "cat" "wc" outfile
// < infile cat | wc > outfile
// check path
void    execute(char *arg, char **envp)
{
	write(1, "\nin execute\n", 12);
	char **com = ft_split(arg, ' ');
//	char *path = find_path();
	execve("/home/bruno/42/pipex/infile", com, envp);
	perror("execve");// dont use perror 
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

void	child_process(int *fd, char **av, char **envp)
{
	int	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		printf("error");
	close(fd[0]);//close unused path
//	dup2(fd[1], 1);//do i really need to dup?
//	dup2(filein, 0);
	printf("in child\n");//printf dont work if dup2 comes before because stdout becomes fd[1]
	execute(av[2], envp);
	close(fd[1]);
	exit(EXIT_SUCCESS);//dont know if correct
}

void	parent_process(int *fd, char **av, char **envp)
{
	int	fileout = open(av[4], O_WRONLY, 0777);
	if (fileout == -1)
		printf("error");
	close(fd[1]);//close unused path
//	dup2(fd[0], 0);
//	dup2(fileout, 1);
	printf("parent\n");
	wait(NULL);
	execute(av[3], envp);
	close(fd[0]);
}

char	*find_path(char **envp)
{
	char *path;
	int i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W')
			
		i++;
	}
//	return (path);
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	/*int  i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}*/
	printf("%s\n", find_path(envp));
	/*int fd[2];
	pid_t pid;//process id
	if (ac == 5)
	{
		pipe(fd);//make fd be pipe (have 2 ends)//error check
		pid = fork();
		if (pid < 0)//error
			return (ft_putendl("error"), 1);
		else if (pid == 0)//child
			child_process(fd, av, envp);
		else if (pid > 1)
		{
			waitpid(pid, NULL, 0);
			parent_process(fd, av, envp);
		}
		return (0);
	}*/

}
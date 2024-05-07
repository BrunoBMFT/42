#include "../includes/pipex.h"
// ./pipex infile "cat" "wc" outfile
// < infile cat | wc > outfile

char	*find_path(char **envp, char *com)
{
	char *path;
	char *part;
	char **paths;
	int i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, com);
		free (part);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	while (paths[i++])
		free(paths[i]);
	free (paths);
	return (NULL);
}

void	fail(void)
{
	perror("error kek");
	exit(EXIT_FAILURE);
}

void	freecoms(char **com)
{
	int i = 0;
	while (com[i])
	{
		free(com[i]);
		i++;
	}
}

void    execute(char *arg, char **envp)
{
	char **com;
	char *path;
	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
	{
		freecoms(com);
		fail();
	}
	if (execve(path, com, envp) == -1)
		fail();
}

void	child_process(int *fd, char **av, char **envp)
{
	int	filein = open(av[1], O_RDONLY, 0777);
	if (filein == -1)
		printf("error");
	close(fd[0]);//close unused path
	dup2(fd[1], 1);//do i really need to dup?
	dup2(filein, 0);
	execute(av[2], envp);
	close(fd[1]);
	exit(EXIT_SUCCESS);//dont know if correct
}

void	parent_process(int *fd, char **av, char **envp)
{
	int	fileout = open(av[4], O_WRONLY, 0777);
	int	extra = open("/home/bruno/42/pipex/extra", O_WRONLY, 0777);
	if (fileout == -1)
		printf("error");
	close(fd[1]);//close unused path
	dup2(fd[0], 0);//
	dup2(fileout, 1);
	wait(NULL);
	execute(av[3], envp);
	write(extra, "2", 2);
	close(fd[0]);
}


int main(int ac, char **av, char **envp)
{
	int fd[2];
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
	}
}
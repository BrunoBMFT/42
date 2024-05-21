//error checking
#include "./includes/minishell.h"

void	freecoms(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free (cmd);
}
char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;

	i = 0;
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
	freecoms(paths);
	return (NULL);
}

int	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
		freecoms(com);
	if (execve(path, com, envp) == -1)
		error(("exec failed"), 1);
	return (0);
}

void	child1_process(int *fd, char **av, char **envp)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0644);
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(filein, 0);
	close(fd[1]);
	close(filein);
	execute(av[2], envp);
	exit(EXIT_SUCCESS);
}

void	child2_process(int *fd, char **av, char **envp)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[0]);
	close(fileout);
	execute(av[3], envp);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
		child1_process(fd, av, envp);
	pid2 = fork();
	if (pid2 == 0)
		child2_process(fd, av, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
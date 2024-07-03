
// ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex_bonus here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file
// TODO error check
#include "../includes/minishell.h"
char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;
	bool	has_path = false;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			has_path = true;
		i++;
	}
	i = 0;
	if (has_path)
	{
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
	}
	else
		write(2, "No envs\n", 9);
	return (NULL);
}

bool	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
	{
		freecoms(com);
		return (false);
	}
	execve(path, com, envp);
	freecoms(com);
//	error("execution failed", 1);
	return (true);
}

void	child_process(char *av, char **envp, char c_or_l)//c = child, l = last
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDOUT_FILENO);
		close(fd[READ]);
		execute(av, envp);
	}
	close(fd[READ]);
	dup2(fd[WRITE], STDIN_FILENO);
	close(fd[WRITE]);
	waitpid(pid, NULL, 0);
	return ;
}

int	last_process(char *av, char **envp)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
		execute(av, envp);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	if (file == -1)
		error("file failed to open", i);//close fds
	return (file);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	pid;
	int		fd[2];
	char	*line;

	if (ac < 6)
		error(WRONGHEREDOC, 1);
	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();//error check
	if (pid == 0)
	{
		close (fd[WRITE]);
		line = NULL;
		while (1)
		{
			line = get_next_line(0);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
		}
//		close(fd[1]);
	}
	else
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDIN_FILENO);
//		close(fd[WRITE]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **envp)
{
	int	status = 0;
	int	i;
	int fileout;
	int filein;

	if (ac < 5)
		return (ft_putendl_fd("wrong arguments", 2), 0);
	if (ft_strnstr(av[1], "here_doc", 8))
	{
		i = 3;
		fileout = open_file(av[ac - 1], 0);
		if (fileout == -1)
			error(av[ac - 1], 1);//check if correct
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		filein = open_file(av[1], 2);
		if (filein == -1)
			error(av[1], 1);//check if correct
		fileout = open_file(av[ac - 1], 1);
		if (fileout == -1)
			error(av[ac - 1], 1);//check if correct
		dup2(filein, 0);
		close (filein);
	}
	while (i < ac - 3)
		child_process(av[i++], envp, 'c');
	child_process(av[i++], envp, 'l');
	dup2(fileout, 1);
	close(fileout);
	status = last_process(av[ac - 2], envp);//check if argv is correct
	return (WEXITSTATUS(status));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unused.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/07/04 10:36:24 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"


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
//main
	// if (ft_strnstr(av[1], "here_doc", 8))
	// {
	// 	i = 3;
	// 	fileout = open_file(av[ac - 1], 0);
	// 	if (fileout == -1)
	// 		error(av[ac - 1], 1);//check if correct
	// 	here_doc(av[2], ac);
	// }


int	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	ft_putendl(com[0]);
	path = find_path(envp, com[0]);
	if (!path)
	{
		freecoms(com);
		error(("zsh: command not found"), 127);//		wrong message (command not found) and output exit code
	}
	if (execve(path, com, envp) == -1)
		error(("exec failed"), 1);
	return (0);
}

void	child_process(char *av, char **envp)
{
	int		fd[2];
	pid_t	pid;
	
	if (!av[0])
		error("no cmd1", 0);
	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
		exit(EXIT_SUCCESS);
	}
	else
		waitpid(pid, NULL, 0);
	close(fd[1]);
}

int	last_process(char *av, char **envp)
{
	int		status;
	int		fd[2];
	pid_t	pid;

	if (!av[0])
		error("no cmd2", 127);
	status = 0;
	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[0]);
		dup2(fd[0], STDIN_FILENO);
		execute(av, envp);
		waitpid(pid, &status, 0);
	}
	return (status);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);//check perms, only for here_docs?
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);//check perms
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);//check perms
	if (file == -1)
		error("file failed to open", i);//i here will just let me know which file failed
	return (file);
}

//change dup2 of child to main
//change dup2 of last to main
//change forks to process functions

int	main(int ac, char **av, char **envp)
{
	int		status;
	int		i;

	status = 0;
	if (ac < 5)
		return (ft_putendl_fd(WRONG, 2), 0);
//	if (ft_strncmp(av, "here_doc", 8) == 0)
		//heredoc
	int fileout = open_file(av[ac - 1], 1);
	int filein = open_file(av[1], 2);
	dup2(filein, STDIN_FILENO);//change filein
	close(filein);
	
	i = 2;
	while (i < ac - 3)
		child_process(av[i++], envp);

	dup2(fileout, STDOUT_FILENO);//change fileout
	close(fileout);
	status = last_process(av[i], envp);
	return (WEXITSTATUS(status));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/02 17:58:55 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex_bonus here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file
// ! CHANGE MAKEFILE
// TODO error codes && error messages
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
	if (execve(path, com, envp) == -1)
		error("execution failed", 1);
	return (true);
}

void	child_process(char *av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute(av, envp);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
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
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);//check perms, only for here_docs?
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);//check perms
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);//check perms
	if (file == -1)
		error("file failed to open", i);//i here will just let me know which file failed
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
		close (fd[0]);
		line = NULL;
		while (get_next_line(&line))
		{
//			ft_putendl(line);
//			ft_putendl(limiter);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(0);
		}
//		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
//		close(fd[0]);
		wait(NULL);//use waitpid
	}
}

int	main(int ac, char **av, char **envp)
{
	int	status = 0;
	int	i;
	int fileout;
	int filein;

	if (ac < 5)
		return (ft_putendl_fd(WRONGBONUS, 2), 0);
	if (ft_strnstr(av[1], "here_doc", 8))
	{
		i = 3;
		fileout = open_file(av[ac - 1], 0);
		here_doc(av[2], ac);
	}
	else
	{
		i = 2;
		fileout = open_file(av[ac - 1], 1);
		filein = open_file(av[1], 2);
		dup2(filein, STDIN_FILENO);
		close (filein);
	}
	while (i < ac - 2)
		child_process(av[i++], envp);
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
//	status = last_process(av[ac - 2], envp);//check if argv is correct
	return (WEXITSTATUS(status));
}
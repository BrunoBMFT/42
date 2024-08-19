/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/07/04 12:13:07 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// ./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex_bonus here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file
bool	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
		return (freecoms(com), false);
	execve(path, com, envp);
	freecoms(com);
	return (true);
}

void	child_process(char *av, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid < 0)
		error("pid error", 0);
	else if (pid == 0)
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		if (!execute(av, envp) || !av || av[0] == ' ')
			error2(av, 1, fd);
	}
	close(fd[WRITE]);
	close(fd[READ]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, NULL, 0);
	return ;
}

int	last_process(char *av, char **envp)
{
	int		status;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid < 0)
		error("pid error", 0);
	if (pid == 0)
	{
		if (!execute(av, envp) || !av || !av[0] == ' ')
			error2(av, 127, 0);
	}
	waitpid(pid, &status, 0);
	return (status);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0644);
	if (file == -1)
		error("file failed to open", i);//close fds
	return (file);
}

int	main(int ac, char **av, char **envp)
{
	int	status = 0;
	int	i;
	int fileout;
	int filein;

	if (ac < 5)
		return (ft_putendl_fd(WRONGBONUS, 2), 0);
	i = 2;
	filein = open_file(av[1], 2);
	if (filein == -1)
		error(av[1], 1);
	fileout = open_file(av[ac - 1], 1);
	if (fileout == -1)
		error(av[ac - 1], 1);
	dup2(filein, STDIN_FILENO);
	close (filein);		
	while (i < ac - 2)
	{
		child_process(av[i], envp);
		i++;
	}
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	status = last_process(av[ac - 2], envp);//check if argv is correct
	return (WEXITSTATUS(status));
}
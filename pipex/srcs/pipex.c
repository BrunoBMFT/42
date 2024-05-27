/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/27 22:26:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// !  ./pipex <file1> <cmd1> <cmd2> <file2>
// TODO wrong message (command not found) and output exit code
// TODO error message of command not found should output the command
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
		error("exec failed", 1);
	return (true);
}

void	child1_process(int *fd, char **av, char **envp)
{
	int	filein;

	if (!av[2][0])
		error("no cmd1", 0);
	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
		error(av[1], 0);
	close(fd[0]);
	dup2(fd[1], 1);
	dup2(filein, 0);
	close(fd[1]);
	close(filein);
	if (!execute(av[2], envp))
		error2(av[2], 1);
	exit(EXIT_SUCCESS);
}

void	child2_process(int *fd, char **av, char **envp)
{
	int	fileout;

	if (!av[3][0])
		error("no cmd2", 127);
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error(av[3], 0);
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[0]);
	close(fileout);
	if (!execute(av[3], envp))
		error2(av[3], 1);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	if (ac != 5)
		return (ft_putendl_fd(WRONG, 2), 0);
	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid1 = fork();
	if (pid1 < 0)
		error("pid1 error", 0);
	else if (pid1 == 0)
		child1_process(fd, av, envp);
	pid2 = fork();
	if (pid2 < 0)
		error("pid2 error", 0);
	else if (pid2 == 0)
		child2_process(fd, av, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
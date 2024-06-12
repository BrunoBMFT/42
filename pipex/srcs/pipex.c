/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/12 18:16:52 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// TODO cat dev random
// TODO filein falied to open -> close fds
// TODO remove infile before eval

void	child1_process(int *fd, char **av, char **envp)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
	{
		close(fd[0]);//can be out?
		close(fd[1]);	
		error(av[1], 0);
	}
	close(fd[0]);
	dup2(filein, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(filein);
	if (!execute(av[2], envp))
		error2(av[2], 1);
	exit(EXIT_SUCCESS);
}

void	child2_process(int *fd, char **av, char **envp)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
	{
		close(fd[1]);
		close(fd[0]);
		error(av[3], 0);
	}
	close(fd[1]);
	dup2(fd[0], 0);
	dup2(fileout, 1);
	close(fd[0]);
	close(fileout);
	if (!execute(av[3], envp))
		error2(av[3], 127);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid[2];
	int		status;
	int		i;

	status = 0;
	if (ac != 5)
		return (ft_putendl_fd(WRONG, 2), 1);
	if (pipe(fd) == -1)
		error("pipe failed", 1);
	i = 0;
	while (i < 2)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			error("pid error", 0);
		else if (pid[i] == 0)
		{
			if (i == 0)
				child1_process(fd, av, envp);
			else if (i == 1)
				child2_process(fd, av, envp);
		}
		if (i == 0)
			waitpid(pid[i], NULL, WNOHANG);
		else
			waitpid(pid[i], &status, WNOHANG);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	return (WEXITSTATUS(status));
}

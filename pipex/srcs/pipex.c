/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/10 15:37:14 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// ./pipex infile "cat" "wc" outfile
// < infile cat | wc > outfile

int	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
		return (freecoms(com), error("no path", 0), 0);
	if (execve(path, com, envp) == -1)
		error("exec fail", 0);
	return (0);
}

void	child_process(int *fd, char **av, char **envp)
{
	int	filein;

	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
		error("filein failed to open", 0);
	close(fd[0]);
	dup2(fd[1], 1);//dup fd write to write
	dup2(filein, 0);//dup in to stdin
	execute(av[2], envp);
	close(fd[1]);
	exit(EXIT_SUCCESS);//might not need
}

void	parent_process(int *fd, char **av, char **envp)
{
	int	fileout;

	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error("fileout failed to open", 0);
	close(fd[1]);
	dup2(fd[0], 0);//dup fd read to read
	dup2(fileout, 1);//dup out to stdout (so it outputs tou outfile)
	wait(NULL);
	execute(av[3], envp);
	close(fd[0]);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (ac == 5)
	{
		if (pipe(fd) == -1) //makes fd be pipe (have 2 ends)
			error(NULL, 0);
		pid1 = fork();//forks so main process isn't lost
		if (pid1 < 0)
			return (ft_putendl("error"), 1);
		else if (pid1 == 0)
		{
			pid2 = fork();//makes the 2 processes we'll execve
			if (pid2 < 0)
				return (ft_putendl("error"), 1);
			else if (pid2 == 0)
				child_process(fd, av, envp);
			waitpid(pid2, NULL, 0);//waits till child is done
			parent_process(fd, av, envp);
		}
	}
	else
		ft_putendl_fd("wrong: ./pipex <file1> <cmd1> <cmd2> <file2>", 2);
	return (0);
}

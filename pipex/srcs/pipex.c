/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/10 17:29:59 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// TODO wrong message (command not found) and output exit code
// ! valgrind --track-origins=yes --trace-children=yes --track-fds=yes ./pipex infile "cat" "caf" outfile
int	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)
	{
		freecoms(com);
		error(("no path"), 127);//		wrong message (command not found) and output exit code
	}
	if (execve(path, com, envp) == -1)
		error(("exec failed"), 1);
	return (0);
}

void	child1_process(int *fd, char **av, char **envp)
{
	int	filein;

	if (!av[2][0])
		error("no cmd1", 0);
	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
		error("filein failed to open", 0);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[1]);
	close(filein);
	execute(av[2], envp);
	exit(EXIT_SUCCESS);
}

void	child2_process(int *fd, char **av, char **envp)
{
	int	fileout;

	if (!av[3][0])
		error("no cmd2", 127);
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error("fileout failed to open", 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
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
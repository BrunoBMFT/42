/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/15 20:33:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// ! UNDERSTAND PIPE AND WHICH FD IS WHICH AND EXECVE
// ! PUT FLAGS IN MAKEFILE
// ! 2 ERROR MESSAGES RUNNING AT THE SAME TIME
bool	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');//free this, in case execve fails, there will be leaks
	path = find_path(envp, com[0]);
	if (!path)
	{
		freecoms(com);
		return (false);
	}
	// TODO execve is tricked into thinking he's reading from 0 and writing to 1
	// TODO instead is reading from fd[1] (read) and writing to fd[0] (write)
	execve(path, com, envp);
	freecoms(com);
//	error("execution failed", 1);
	return (false);
}

void	child1_process(int *fd, char **av, char **envp)// ! change variable fd to diff name
{
	int	filein;

	if (!av[2][0])
		close_fds_null(fd);
	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
		close_fds_exit(fd, av[1]);
	close(fd[WRITE]);// TODO why does this one close
	dup2(filein, STDIN_FILENO);//* execve reads from 0, so we shortcut 0 to filein so he reads filein
	dup2(fd[READ], STDOUT_FILENO);// * execve writes to 1, so we make 1 a "shortcut" to fd[read]
	close(fd[READ]);// TODO why does this one close
	close(filein);// TODO why does this one close before execve
	if (!execute(av[2], envp))
		error2(av[2], 1);
}

void	child2_process(int *fd, char **av, char **envp)// ! change variable fd to diff name
{
	int	fileout;

	if (!av[3][0])
		close_fds_null(fd);
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		close_fds_exit(fd, av[4]);
	close(fd[READ]);// TODO why does this one close
	dup2(fd[WRITE], STDIN_FILENO);// * execve reads from 0, so we shortcut 0 to fd[1](write)
	dup2(fileout, STDOUT_FILENO);// * execve writes to 1, so we make 1 a shortcut to fileout
	close(fd[WRITE]);// TODO why does this one close
	close(fileout);// TODO why does this one close before execve
	if (!execute(av[3], envp))
		error2(av[3], 127);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	if (ac != 5)
		return (ft_putendl_fd(WRONG, 2), 1);
	//fd[WR] can only receive info from fd[RD] after fd[RD] closes (aka done being written to)
	if (pipe(fd) == -1)// TODO how is it being piped
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
	close(fd[WRITE]);
	close(fd[READ]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}

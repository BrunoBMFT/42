/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:02:41 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
//exit codes, error messages
//rename vars and funcs
//check fds and leaks

char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;

	i = 0;
	if (access(com, F_OK) == 0)
		return (com);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part = ft_strjoin(paths[i], "/");//use ft_strjoin2
		path = ft_strjoin(part, com);
		free (part);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
	}
	free_array(paths);
	return (NULL);
}

bool	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	if (!arg || !*arg)
	{
		ft_printf_fd(2, "No command\n");
		exit(1);
	}
	com = ft_split(arg, ' ');
	path = find_path(envp, com[0]);
	if (!path)//check access
	{
		ft_printf_fd(2, "%s: command not found\n", com[0]);
		free_array(com);
		//find a way to free pids
		exit (1);
	}
	execve(path, com, envp);//test commenting the execve
	ft_printf_fd(2, "execve() failed\n");
	free_array(com);
	exit (1);
}

void	child_process(char *av, char **envp, t_pipex *pipex, bool last)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error(1);
	pid = new_fork(pipex);
	if (pid < 0)
		error(1);
	if (pid == 0)
	{
		close(fd[READ]);
		if (!last)
			dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		execute(av, envp);
	}
	close(fd[WRITE]);
	dup2(fd[READ], STDIN_FILENO);
	close(fd[READ]);
	return ;
}

void	redirect(char *argv, int side)
{
	int	file;

	file = 0;
	if (side == 0)
		file = open(argv, O_RDONLY, 0644);
	else if (side == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		ft_printf_fd(2, "Error: open() failed\n");
		exit (1);
	}
	dup2(file, side);
	close (file);
}

int	main(int ac, char **av, char **envp)
{
	int	status = 0;
	int	i;
	t_pipex pipex;
	pipex.pids = NULL;

	if (ac < 5)
		return (ft_putendl_fd(WRONGBONUS, 2), 0);
	if (!envp || !*envp)
		return (ft_putendl_fd(NOENV, 2), 0);
	redirect(av[1], STDIN_FILENO);
	redirect(av[ac - 1], STDOUT_FILENO);
	
	pipex.pids = ft_calloc_pids(ac - 2);
	i = 2;
	
	while (i < ac - 2)
		child_process(av[i++], envp, &pipex, false);
	child_process(av[i], envp, &pipex, true);
	
	status = run_waitpids(&pipex);
	free (pipex.pids);
	return (WEXITSTATUS(status));
}
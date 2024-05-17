/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/17 15:41:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file
// TODO error check
int	execute(char *arg, char **envp)
{
	char	**com;
	char	*path;

	com = ft_split(arg, ' ');
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

	if (pipe(fd) == -1)
		error("pipe failed", 1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);//write
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
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

int	main(int ac, char **av, char **envp)
{
	int status = 0;
	if (ac < 5)
		return (ft_putendl_fd(WRONGBONUS, 2), 0);
	if (ft_strnstr(av[2], "here_doc", 8))
		ft_printf("here_doc");
	else
	{
		int i = 2;
		int fileout = open_file(av[ac - 1], 1);
		int filein = open_file(av[1], 2);
		dup2(filein, STDIN_FILENO);
		close (filein);
		while (i < ac - 2)
			child_process(av[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
		status = last_process(av[ac - 2], envp);//check if argv is correct
	}
	return (WEXITSTATUS(status));
}
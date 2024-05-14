/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:59:37 by brfernan          #+#    #+#             */
/*   Updated: 2024/05/12 20:08:46 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
// TODO error message of command not found should output the command
// ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
// < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

// ./pipex here_doc LIMITER cmd cmd1 file
// cmd << LIMITER | cmd1 >> file

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

void	child_process(int *fd, char *av, char **envp)
{
	int	filein;

	if (!av[0])
		error("no cmd1", 0);
	filein = open(av[1], O_RDONLY, 0644);
	if (filein == -1)
		error("filein failed to open", 0);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	dup2(filein, STDIN_FILENO);
	close(fd[1]);
	close(filein);
	execute(av, envp);
	exit(EXIT_SUCCESS);
}

void	last_process(int *fd, char *av, char **envp)
{
	int	fileout;

	if (!av[0])
		error("no cmd2", 127);
	fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fileout == -1)
		error("fileout failed to open", 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(fileout, STDOUT_FILENO);
	close(fd[0]);
	close(fileout);
	execute(av, envp);
	exit(EXIT_SUCCESS);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

int	main(int ac, char **av, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;
	int		i;

	status = 0;
	if (ac < 5)
		return (ft_putendl_fd(WRONG, 2), 0);
	if (ft_strncmp(av, "here_doc", 8) == 0){
		//heredoc
	}
	else
	{
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
	}
	return (WEXITSTATUS(status));
}
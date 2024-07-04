/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:35 by brfernan          #+#    #+#             */
/*   Updated: 2024/07/04 12:09:42 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

bool	path_exists(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			return (true);
		i++;
	}
	return (false);
}

char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;

	i = 0;
	if (!path_exists(envp))
		return (NULL);
	if (access(com, F_OK) == 0)
		return (com);
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, com);
		free (part);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
	}
	freecoms(paths);
	return (NULL);
}

void	freecoms(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free (cmd);
}


void	close_fds_exit(int *fd, char *str)
{
	close(fd[0]);
	close(fd[1]);
	error(str, 1);
}

void	error(char *str, int code)
{
	write(2, "bash: ", 6);
	perror(str);
	exit(code);
}

void	error2(char *str, int code, int *fd)
{
	char	**new;

	close(fd[0]);
	close(fd[1]);
	new = ft_split(str, ' ');
	write(2, new[0], ft_strlen(new[0]));
	write(2, ": command not found\n", 20);
	freecoms(new);
	exit(code);
}

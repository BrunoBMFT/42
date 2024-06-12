/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:35 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/12 17:34:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		error("execution failed", 1);
	return (true);
}

char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part, com);
		free (part);
		if (access(path, F_OK) == 0)
			return (path);
		free (path);
		i++;
	}
	i = -1;
	freecoms(paths);
	return (NULL);
}

void	error(char *str, int code)
{
	write(2, "bash: ", 6);
	perror(str);
	exit(code);
}

void	error2(char *str, int code)
{
	char	**new;

	new = ft_split(str, ' ');
	write(2, new[0], ft_strlen(new[0]));
	freecoms(new);
	write(2, ": command not found\n", 20);
	exit(code);
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

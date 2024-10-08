/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:35 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/16 12:27:01 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp, char *com)
{
	char	*path;
	char	*part;
	char	**paths;
	int		i;
	bool	has_path = false;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4) != 0)
			has_path = true;
		i++;
	}
	i = 0;
	if (has_path)
	{
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
	}
	else
		write(2, "No envs\n", 9);
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

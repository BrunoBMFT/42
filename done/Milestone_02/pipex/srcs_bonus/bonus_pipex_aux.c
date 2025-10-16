/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:40:35 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 04:12:04 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	new_fork(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (pipex->pids[i] != -1)
		i++;
	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
	{
		ft_printf_fd(2, "fork() error\n");
		return (-1);
	}
	return (pipex->pids[i]);
}

void	*ft_calloc_pids(int size)
{
	int		*dest;
	int		i;

	dest = malloc(sizeof(pid_t) * size);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dest[i] = -1;
		i++;
	}
	return (dest);
}

int	run_waitpids(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (pipex->pids[i] != -1)
	{
		waitpid(pipex->pids[i], &status, 0);
		pipex->pids[i] = -1;
		i++;
	}
	return (WEXITSTATUS(status));
}


// char	*find_path(char **envp, char *com)
// {
// 	char	*path;
// 	char	*part;
// 	char	**paths;
// 	int		i;
// 	bool	has_path = false;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH", 4) != 0)
// 			has_path = true;
// 		i++;
// 	}
// 	i = 0;
// 	if (has_path)
// 	{
// 		while (ft_strnstr(envp[i], "PATH", 4) == 0)
// 			i++;
// 		paths = ft_split(envp[i] + 5, ':');
// 		i = 0;
// 		while (paths[i])
// 		{
// 			part = ft_strjoin(paths[i], "/");
// 			path = ft_strjoin(part, com);
// 			free (part);
// 			if (access(path, F_OK) == 0)
// 				return (path);
// 			free (path);
// 			i++;
// 		}
// 		i = -1;
// 		freecoms(paths);
// 	}
// 	else
// 		write(2, "No envs\n", 9);
// 	return (NULL);
// }



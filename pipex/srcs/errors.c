/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:24:29 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/16 23:21:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	error2(char *str, int code, int *fd, bool has_fd)
{
	char	**new;

	if (has_fd == true)
	{
		close(fd[0]);
		close(fd[1]);
	}
	new = ft_split(str, ' ');
	write(2, new[0], ft_strlen(new[0]));
	write(2, ": command not found\n", 20);
	freecoms(new);
	exit(code);
}

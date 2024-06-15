/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:24:29 by brfernan          #+#    #+#             */
/*   Updated: 2024/06/15 20:32:22 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds_exit(int *fd, char *str)
{
	close(fd[0]);
	close(fd[1]);
	error(str, 1);
}

void	close_fds_null(int *fd)
{
	close(fd[0]);
	close(fd[1]);
	write(2, "command '' not found\n", 21);
	exit(0);
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

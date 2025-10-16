/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 20:24:29 by brfernan          #+#    #+#             */
/*   Updated: 2024/12/16 01:10:04 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_fds_exit(int *fd)//fix
{
	close(fd[0]);
	close(fd[1]);
	error(1);
}

void	error(int code)
{
	write(2, "Fatal error", 12);
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
	free_array(new);
	exit(code);
}

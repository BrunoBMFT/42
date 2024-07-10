/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:50:28 by bruno             #+#    #+#             */
/*   Updated: 2024/07/10 17:41:27 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_echo(t_jobs *job)//fix echo "   hello"
{
	bool	nl;
	
	nl = true;
	if (ft_strnstr(job->cmd, "-n", 7))
		nl = false;
	ft_printf("%s", job->execd);
	if (nl == true)
		ft_nl_fd(1);
}

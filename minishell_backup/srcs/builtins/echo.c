/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 04:38:31 by bruno             #+#    #+#             */
/*   Updated: 2024/10/13 21:11:28 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//echo ola   ""    bruno
//maybe use malloced string and print that string?
int	caught_echo(t_jobs *job)
{
	bool	nl;
	int		i;

	i = 1;
	if (!job->job[1])
		return (ft_nl_fd(1), 0);
	if (ft_strcmp(job->job[1], "-n") == 0)
		i++;
	while (job->job[i])
	{
		ft_printf("%s", job->job[i]);
		if (job->job[i + 1])
			ft_printf(" ");
		i++;
	}
	if (ft_strcmp(job->job[1], "-n"))
		ft_printf("\n");
	return (0);
}

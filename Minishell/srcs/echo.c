/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:50:28 by bruno             #+#    #+#             */
/*   Updated: 2024/07/03 19:50:53 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	caught_echo(char *input)//-n gives helloMinishell ->
{
	int		i;
	bool	nl;	
	
	nl = true;
	if (ft_strnstr(input, "-n", 7))
	{
		nl = false;
		i = 7;
	}
	else
		i = 4;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		write(1, &input[i], 1);
		i++;
	}
	if (nl == true)
		ft_nl_fd(1);
}

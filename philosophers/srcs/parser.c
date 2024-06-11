/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:45 by bruno             #+#    #+#             */
/*   Updated: 2024/06/11 02:15:30 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//number_of_philosophers   time_to_die   time_to_eat  
//time_to_sleep  [number_of_times_each_philosopher_must_eat]
// TODO error messages
#include "../includes/philosophers.h"

bool	only_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (ft_putendl(WRONGARGS), false);
			j++;
		}
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < 0)
			return (ft_putendl(BIGINT), false);
		i++;
	}
	if (ft_atol(av[1]) < 1)
		return (ft_putendl(NOPHILO), false);
	return (true);
}

bool	parser(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (ft_putendl("wrong number of arguments"), false);
	if (!only_digits(av))
		return (false);
	return (true);
}

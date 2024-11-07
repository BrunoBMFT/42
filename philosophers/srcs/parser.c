/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:45 by bruno             #+#    #+#             */
/*   Updated: 2024/11/07 21:42:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//number_of_philosophers   time_die   time_eat  
//time_sleep  [number_of_times_each_philosopher_must_eat]
#include "../includes/philosophers.h"

bool	num_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check(char **av)
{
	int		i = 0;
	size_t	num;

	i = 1;
	while (av[i])
	{
		if (!num_check(av[i]))
			return (printf("not a number\n"), false);
		num = ft_atol(av[i]);
		if (num <= 0 || num > INT_MAX)
			return (printf("wrong size\n"), false);
		i++;
	}
	return (true);
}

bool	parser(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong number of arguments\n"), false);
	if (!check(av))
		return (false);
	return (true);
}

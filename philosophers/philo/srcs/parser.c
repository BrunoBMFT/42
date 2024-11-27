/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:33:45 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 22:08:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		i;
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

bool	parser(int ac, char **av, t_table *table)
{
	if (ac < 5 || ac > 6)
		return (printf("wrong number of arguments\n"), false);
	if (!check(av))
		return (false);
	if (!init_table(table, av))
		return (false);
	return (true);
}

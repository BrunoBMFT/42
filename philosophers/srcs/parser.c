/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:45 by bruno             #+#    #+#             */
/*   Updated: 2024/09/23 02:53:38 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//number_of_philosophers   time_to_die   time_to_eat  
//time_to_sleep  [number_of_times_each_philosopher_must_eat]
#include "../includes/philosophers.h"

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

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

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9' && result <= INT_MAX)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

bool	size_check(char **av)
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
	if (!size_check(av))
		return (false);
	return (true);
}

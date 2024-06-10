/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:29:37 by jomendes          #+#    #+#             */
/*   Updated: 2024/05/31 13:41:48 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				write (2, "Wrong augments\n", 15);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_for_values(t_info *info)
{
	if (info->n_philos <= 0 || info->time_to_die <= 0 || \
	info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	ft_atol(char *str)
{
	int		i;
	long	result;
	int		signal;

	i = 0;
	result = 0;
	signal = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		if (result >= INT_MAX)
			return (-1);
		i++;
	}
	return (result * signal);
}

unsigned long	get_time(unsigned long start_time)
{
	struct timeval	time;
	unsigned long	l;
	unsigned long	s;
	unsigned long	u;

	gettimeofday(&time, NULL);
	s = (time.tv_sec * 1000);
	u = (time.tv_usec / 1000);
	l = s + u;
	return (l - start_time);
}

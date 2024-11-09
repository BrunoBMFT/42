/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:45 by bruno             #+#    #+#             */
/*   Updated: 2024/11/09 01:16:56 by bruno            ###   ########.fr       */
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

void	single(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	usleep(philo->info.time_die * 1000);
	printf("%d 1 died\n", philo->info.time_die);
	ft_lstclear(&philo);
}

bool	init_table(t_table *table, char **av)
{
	t_philo			*philo;
	t_philo			*temp;
	int				i;

	i = 0;
	philo = NULL;
	table->start_time = get_time();
	pthread_mutex_init(&table->is_running_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	while (i < ft_atoi(av[1]))
	{
		temp = ft_lstnew(i, av);//free temp in error
		if (!temp)
			return (ft_lstclear(&table->philo), false);
		temp->table = table;
		ft_lstadd_back(&philo, temp);
		i++;
	}
	if (ft_atoi(av[1]) == 1)
		return (single(philo), false);
	table->philo = philo;
	table->is_running = true;
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

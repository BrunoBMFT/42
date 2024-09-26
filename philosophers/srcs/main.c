/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/09/25 02:56:56 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	join_threads(t_table *table)
{
	t_philo	*start;
	
	start = table->philo;
	while (table)
	{
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == start)
			return ;//return ft_lstclear, NULL
	}
}

void	eat_action(t_philo *philo)
{
	printf("%d trying\n", philo->id);
	pthread_mutex_lock(&philo->fork);
	print_tookfork(calculate_time(philo), philo->id);
	
	printf("%d trying\n", philo->id);
	pthread_mutex_lock(&philo->next->fork);
	print_tookfork(calculate_time(philo), philo->id);

	print_eating(calculate_time(philo), philo->id);

	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);

	usleep(philo->info.time_to_eat * 1000);//very broken
}

void	*start_philo(void *arg)
{
	t_table *table = (t_table *) arg;
	printf("ptid: %d\n", table->philo->id);
	pthread_mutex_lock(&table->sim_mutex);
	eat_action(table->philo);
	pthread_mutex_unlock(&table->sim_mutex);
	//sleep
	//think
}

int	main(int ac, char **av)
{
/* 	if (!parser(ac, av))
		return (1); */
	if (!av[1])
		return (1);

	t_table		table;
	init_table(&table, av);

	t_philo	*first = table.philo;
	while (table.philo)
	{
		pthread_create(&table.philo->ptid, NULL, &start_philo, &table);
		table.philo = table.philo->next;
		if (table.philo == first)
			return (join_threads(&table), 0);
	}

	return (0);
}

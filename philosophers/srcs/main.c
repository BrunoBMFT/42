/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/09/28 23:00:43 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo time_die time_eat time_sleep [num__philo_must_eat]

void	join_threads(t_table *table)
{
	t_philo	*start;
	
	start = table->philo;
	while (table)
	{
		pthread_join(table->philo->ptid, NULL);
		table->philo = table->philo->next;
		if (table->philo == start)
			return ;
	}
}

void	lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	print_action(calculate_time(philo), philo->id, TOOKFORK);

	pthread_mutex_lock(&philo->next->fork);
	print_action(calculate_time(philo), philo->id, TOOKFORK);
}

void	unlock(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	eat_action(t_philo *philo)
{
	lock(philo);

	print_action(calculate_time(philo), philo->id, EATING);

	usleep(philo->info.time_to_eat * 1000);//very broken
	
	philo->has_eaten = true;

	unlock(philo);
}

void	sleep_action(t_philo *philo)
{
	print_action(calculate_time(philo), philo->id, SLEEPING);
	philo->has_eaten = false;
	usleep(philo->info.time_to_sleep * 1000);
}

void	*start_philo(void *arg)
{
	//while (num_times_eat != 0)// if not specified, numtimeeat is -1
	t_table *table = (t_table *) arg;//make this t_philo
	eat_action(table->philo);
	if (table->philo->has_eaten)
		sleep_action(table->philo);
/* 	t_philo	*philo = (t_philo *) arg;
	eat_action(philo);
	if (philo->has_eaten)
		sleep_action(philo); */
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
	t_philo	*temp = first;
	while (table.philo)
	{
		pthread_create(&table.philo->ptid, NULL, &start_philo, &table);
		table.philo = table.philo->next;
		if (table.philo == first)
			return (join_threads(&table), 0);
	}

	return (0);
}

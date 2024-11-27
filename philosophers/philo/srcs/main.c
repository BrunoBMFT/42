/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 17:27:32 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	stop_sim(t_table *table)
{
	pthread_mutex_lock(&table->is_running_mutex);
	table->is_running = false;
	pthread_mutex_unlock(&table->is_running_mutex);
	join_threads(table);
	return (1);
}

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*first;

	if (!parser(ac, av, &table))
		return (1);
	first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL, &philo_routine, table.philo))
			return (stop_sim(&table));
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	pthread_create(&table.observer, NULL, &observe_experiment, &table);
	join_threads(&table);
	return (0);
}

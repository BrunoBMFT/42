/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/07 22:29:16 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo timedie timeeat timesleep [num__philo_must_eat]

bool check_if_running(t_table *table)
{
	t_philo	*current;

	current = table->philo;
	while (current)
	{
		if (is_dead(current))
		{
			set_bool(&table->is_running_mutex, &table->is_running, false);
			print_action(current, DIED);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

void *observe_experiment(void *tab)
{
    t_table *table;

    table = (t_table *)tab;
    while (get_bool(&table->is_running_mutex, table->is_running))//doesnt end on death
    {
		if (check_if_running(table))
			break ;
        usleep(50);
    }
    return (NULL);
}

int	main(int ac, char **av)
{
	t_table table;
	t_philo *first;

	if (!parser(ac, av))
		return (1);
	if (!init_table(&table, av))
		return (0);
	first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL, &philo_routine, table.philo))
			return (stop_sim(table.philo), join_threads(&table), 0);
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	pthread_create(&table.observer, NULL, &observe_experiment, &table);
	join_threads(&table);
	return (0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/09 01:18:17 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo timedie timeeat timesleep [num__philo_must_eat]
//4 philos infinite case doesnt infinite, maybe think time is wrong

bool observer_check(t_table *table)
{
	t_philo	*current;

	current = table->philo;
	while (current)
	{
		if (is_dead(current))
		{
			print_action(current, DIED);//wrong philo
			return (false);
		}
		if (get_int(&current->info.num_times_eat_mutex, current->info.num_times_eat) == 0)
		{
			set_bool(&current->table->is_running_mutex, &current->table->is_running, false);//should i wait for everyone to think?
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
    while (get_bool(&table->is_running_mutex, table->is_running))
    {
		if (observer_check(table))
			break ;
        usleep(50);
    }
    return (NULL);
}

int	main(int ac, char **av)
{
	t_table table;
	t_philo *first;

	if (!parser(ac, av, &table))
		return (1);
	first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL, &philo_routine, table.philo))
			return (set_bool(&table.is_running_mutex, &table.is_running, false), join_threads(&table), 0);
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	pthread_create(&table.observer, NULL, &observe_experiment, &table);
	join_threads(&table);
	return (0);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:30:40 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 00:51:47 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//dont use it twice, use only on observer or actions
bool	is_dead(t_philo *philo)
{
	int	time_since_last;

	time_since_last = get_time()
		- get_int(&philo->last_meal_mutex, philo->last_meal);
	if (time_since_last > philo->info.time_die)
	{
		//put this in check_if_running func
		set_bool(&philo->table->is_running_mutex,
			&philo->table->is_running, false);
		return (true);
	}
	return (false);
}

bool	observer_check(t_table *table)
{
	t_philo	*current;
	int		all_done = 0;

	current = table->philo;
	while (current)//never cycles????????????
	{
		if (is_dead(current))
			return (print_action(current, DIED), false);
		if (get_int(&current->info.num_times_eat_mutex, current->info.num_times_eat) == 0)
		{
			all_done++;
			printf("id %d is done %d\n", current->id, all_done);
		}
		if (all_done == table->philo_num)
		{
			printf("id %d\n", current->id);
			//should i wait for everyone to think? yes
			set_bool(&current->table->is_running_mutex,
				&current->table->is_running, false);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

void	*observe_experiment(void *tab)
{
	t_table	*table;

	table = (t_table *)tab;
	while (1)
	{
		int initiated = get_int(&table->is_running_mutex, table->initialized);
		if (initiated == table->philo_num)
			break;
		usleep(100);
	}
	while (is_sim_running(table))
	{
		if (observer_check(table))
			break ;
		usleep(50);
	}
	return (NULL);
}

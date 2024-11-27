/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:30:40 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 17:27:17 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	is_dead(t_philo *philo)
{
	int	time_since_last;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_last = get_time() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (time_since_last > philo->info.time_die)
	{
		pthread_mutex_lock(&philo->table->is_running_mutex);
		philo->table->is_running = false;
		pthread_mutex_unlock(&philo->table->is_running_mutex);
		return (true);
	}
	return (false);
}

bool	observer_check(t_table *table)
{
	t_philo	*current;
	int		all_done;
	
	all_done = 0;
	pthread_mutex_lock(&table->print_mutex);
	current = table->philo;
	pthread_mutex_unlock(&table->print_mutex);
	while (current)
	{
		if (is_dead(current))
			return (print_action(current, DIED), false);
		pthread_mutex_lock(&current->info.num_times_eat_mutex);
		int num_times = current->info.num_times_eat;
		pthread_mutex_unlock(&current->info.num_times_eat_mutex);
		if (num_times == 0)
			all_done++;
		if (all_done == table->philo_num)
		{
			pthread_mutex_lock(&current->table->is_running_mutex);
			current->table->is_running = false;
			pthread_mutex_unlock(&current->table->is_running_mutex);
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
	while (is_sim_running(table))
	{
		if (observer_check(table))
			break ;
		usleep(50);
	}
	return (NULL);
}

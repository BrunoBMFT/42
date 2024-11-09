/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:00:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/09 01:17:58 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	is_dead(t_philo *philo)//dont use it twice, use only on observer or actions
{
	int	time_since_last;

	set_int(&philo->last_meal_mutex, &time_since_last, get_time() - philo->last_meal);
	if (time_since_last < philo->info.time_die)
		return (false);//still alive
	set_bool(&philo->table->is_running_mutex, &philo->table->is_running, false);//put this in check_if_running func
	return (true);
}

bool	usleep_and_update(t_philo *philo, int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_dead(philo))
			return (false);
		usleep(10);
	}
	set_int(&philo->last_meal_mutex, &philo->last_meal, get_time());	
	if (philo->info.num_times_eat == -1)
		return (true);
	set_int(&philo->info.num_times_eat_mutex,
			&philo->info.num_times_eat, (philo->info.num_times_eat - 1));
	return (true);
}

bool	eat_action(t_philo *philo)
{
	lock_forks(philo);
	print_action(philo, EATING);
	if (!usleep_and_update(philo, philo->info.time_eat))
		return(false);
	unlock_forks(philo);
	return (true);
}

bool	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	if (!usleep_and_update(philo, philo->info.time_sleep))
		return(false);
	return (true);
}

bool	think_action(t_philo *philo)
{
	print_action(philo, THINKING);
	if (!usleep_and_update(philo, philo->info.time_think))
		return(false);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->info.num_times_eat != 0)
	{
		if (!eat_action(philo))
			break;
		if (!sleep_action(philo))
			break;
		if (!think_action(philo))
			break;
	}
	return (NULL);
}
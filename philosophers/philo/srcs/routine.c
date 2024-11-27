/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:00:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 17:41:35 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	usleep_and_update(t_philo *philo, int time)
{
	int	start;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_dead(philo) && is_sim_running(philo->table))
			return (false);
		// if (!is_sim_running(philo->table))
		// 	return (true);
		usleep(10);
	}
	return (true);
}

bool	eat_action(t_philo *philo)
{
	lock_forks(philo);
	print_action(philo, EATING);

	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = get_time();//use start_time for this
	pthread_mutex_unlock(&philo->last_meal_mutex);
	
	pthread_mutex_lock(&philo->info.num_times_eat_mutex);
	philo->info.num_times_eat--;
	pthread_mutex_unlock(&philo->info.num_times_eat_mutex);

	if (!usleep_and_update(philo, philo->info.time_eat))
		return (false);
	unlock_forks(philo);
	return (true);
}

bool	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	if (!usleep_and_update(philo, philo->info.time_sleep))
		return (false);
	return (true);
}

bool	think_action(t_philo *philo)
{
	print_action(philo, THINKING);
	if (!usleep_and_update(philo, philo->info.time_think))
		return (false);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->info.num_times_eat != 0)
	{
		if (!is_sim_running(philo->table))
			break ;
		if (!eat_action(philo))
			break ;
		if (!sleep_action(philo))
			break ;
		if (!think_action(philo))
			break ;
	}
	return (NULL);
}

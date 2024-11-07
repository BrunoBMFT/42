/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:00:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/07 22:32:33 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	usleep_and_update(t_philo *philo, int time)//can change sim status so others finish
{
	int	start;

	start = get_time();
	while (get_time() - start < time)// maybe its <=?
	{
		if (is_dead(philo))
			return ;
		usleep(10);
	}
	set_int(&philo->last_meal_mutex, &philo->last_meal, get_time());	
	if (philo->info.num_times_eat == -1)
		return ;
	set_int(&philo->info.num_times_eat_mutex,
			&philo->info.num_times_eat, (philo->info.num_times_eat - 1));
}

bool	eat_action(t_philo *philo)
{
	lock_forks(philo);
	print_action(philo, EATING);
	usleep_and_update(philo, philo->info.time_eat);
	unlock_forks(philo);
	return (true);
}

bool	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	usleep_and_update(philo, philo->info.time_sleep);
	return (true);
}

bool	think_action(t_philo *philo)
{
	print_action(philo, THINKING);
	usleep_and_update(philo, philo->info.time_think);
	return (true);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo = (t_philo *)arg;
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
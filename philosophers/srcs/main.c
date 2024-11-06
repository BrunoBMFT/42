/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/11/06 16:49:53 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo timedie timeeat timesleep [num__philo_must_eat]

void	update_last_and_num(t_philo *philo)
{
	set_int(&philo->last_meal_mutex, &philo->last_meal, get_time());	
	if (philo->info.num_times_eat == -1)
		return ;
	set_int(&philo->info.num_times_eat_mutex,
			&philo->info.num_times_eat, (philo->info.num_times_eat - 1));
}

bool	is_dead(t_philo *philo)
{
	int	time_since_last;

	time_since_last = get_time() - philo->last_meal;//get_int for mutex safety
	if (time_since_last < philo->info.time_die)
		return (false);//still alive
		
	print_action(philo, DIED);
	stop_sim(philo);


	return (true);
}

void	usleep_without_dying(t_philo *philo, int time)//can change sim status so others finish
{
	int	start;

	start = get_time();
	while (get_time() - start < time)// maybe its <=?
	{
		if (is_dead(philo))
			return ;
		usleep(10);
	}
}

bool	eat_action(t_philo *philo)
{
	if (!is_sim_running(philo))
		return (false);
	lock_forks(philo);
	if (!is_sim_running(philo))// ! dont want it like this
		return (false);
	print_action(philo, EATING);
	update_last_and_num(philo);
	usleep_without_dying(philo, philo->info.time_eat);
	if (!is_sim_running(philo))// ! dont want it like this
		return (false);
		
	unlock_forks(philo);
	return (true);
}

bool	sleep_action(t_philo *philo)
{
	if (!is_sim_running(philo))
		return (false);

	print_action(philo, SLEEPING);
	usleep_without_dying(philo, philo->info.time_sleep);
	
	if (!is_sim_running(philo))// ! dont want it like this
		return (false);
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
//		think_action(philo);
	}
	//close info?
	return (NULL);
}

int	main(int ac, char **av)
{
	if (!parser(ac, av))
		return (1);
	t_table table;
	init_table(&table, av);
	
	t_philo *first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL, &philo_routine, table.philo))
			return (stop_sim(table.philo), join_threads(&table), 0);
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	join_threads(&table);
	return (0);
}



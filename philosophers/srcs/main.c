/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/10/02 02:52:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo time_die time_eat time_sleep [num__philo_must_eat]

void	join_threads(t_philo *philo)
{
	t_philo	*start;
	
	start = philo;
	while (philo)
	{
		pthread_join(philo->ptid, NULL);
		philo = philo->next;
		if (philo == start)
			return ;
	}
}

bool	eat_action(t_philo *philo)
{
	lock(philo);
	print_action(philo, EATING);
	philo->info.last_meal = get_current_time(philo);
	
	usleep(philo->info.time_to_eat * 1000);
	unlock(philo);

	return (true);
}

void	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	usleep(philo->info.time_to_sleep * 1000);
}

bool	is_alive(t_philo *philo)
{
	int	last;

	last = time_since_last(philo);
	if (philo->info.time_to_die < last)
		return (print_action(philo, DIED), false);
	return (true);
}

void	*start_philo(void *arg)
{
	t_philo	*philo = (t_philo *) arg;

	int i = 0;//num eat
	while (i < 2)
	{
/* 		if (!is_alive(philo))//maybe needs to be in each action
			return (NULL);//has to make everything close and exit
*/
		eat_action(philo);
		sleep_action(philo);
		//think
		i++;
	}
	//send close info
	return (NULL);
}

int	main(int ac, char **av)
{
	t_table		table;

	if (!parser(ac, av))
		return (1);

	init_table(&table, av);

	t_philo	*first = table.philo;
	t_philo	*current_philo = first;
	while (current_philo)
	{
		pthread_create(&current_philo->ptid, NULL, &start_philo, current_philo);
		current_philo = current_philo->next;
		if (current_philo == first)
		{
			join_threads(current_philo);
			break ;
		}
	}
	return (0);
}

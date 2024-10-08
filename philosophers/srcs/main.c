/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/10/08 21:12:40 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo timedie timeeat timesleep [num__philo_must_eat]

bool	is_alive(t_philo *philo)
{
	int	last;

	last = time_since_last(philo);
//	printf("last meal %d ago\n", last);
	if (philo->info.time_die < last)
		return (print_action(philo, DIED), false);
	return (true);
}


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

bool	eat_action(t_philo *philo)//maybe bool not needed
{
	lock(philo);
	print_action(philo, EATING);
	philo->info.last_meal = get_time(philo);
	
	usleep(philo->info.time_eat * 1000);
	unlock(philo);

	return (true);
}

bool	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	usleep(philo->info.time_sleep * 1000);
	return (true);
}

bool	think_action(t_philo *philo)
{
	print_action(philo, THINKING);
	usleep(philo->info.time_think * 1000);//timing wrong
	return (true);
}

void	*start_philo(void *arg)
{
	t_philo	*philo = (t_philo *) arg;

	while (philo->info.num_times_eat != 0)
	{
		eat_action(philo);
		sleep_action(philo);
//		think_action(philo);
		philo->info.num_times_eat--;
	}
	//send close info?
	return (void *)NULL;
}

int	main(int ac, char **av)
{
	t_table		table;

	if (!parser(ac, av, &table))
		return (1);

	t_philo	*first = table.philo;
	t_philo	*current_philo = first;
	while (current_philo)
	{
		if (pthread_create(&current_philo->ptid, NULL, &start_philo, current_philo))//check timings
		{
			printf("thread fail\n");
			break ;
		}	
		current_philo = current_philo->next;
		if (current_philo == first)
			break;
	}
	join_threads(current_philo);
	return (0);
}

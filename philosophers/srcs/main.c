/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:41 by bruno             #+#    #+#             */
/*   Updated: 2024/10/02 22:36:52 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//num_of_philo time_die time_eat time_sleep [num__philo_must_eat]

bool	is_alive(t_philo *philo)
{
	int	last;

	last = time_since_last(philo);
	printf("last meal %d ago\n", last);
	if (philo->info.time_to_die < last)
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

bool	eat_action(t_philo *philo)
{
	lock(philo);
	print_action(philo, EATING);
	philo->info.last_meal = get_time(philo);
	
	usleep(philo->info.time_to_eat * 1000);
	unlock(philo);

	return (true);
}

bool	sleep_action(t_philo *philo)
{
	print_action(philo, SLEEPING);
	usleep(philo->info.time_to_sleep * 1000);
	return (true);
}

void	*start_philo(void *arg)
{
	t_philo	*philo = (t_philo *) arg;

	int i = 0;//num eat
	while (i < 2)
	{
/* 		if (!is_alive(philo))//maybe needs to be in each action
			return (NULL);//has to make everything close and exit */

		if (!eat_action(philo))
			return (void *)false;
		if (!sleep_action(philo))
			return (void *)false;
		//think
		i++;
	}
	//send close info
	return (void *)true;
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

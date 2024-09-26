/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:02:06 by bruno             #+#    #+#             */
/*   Updated: 2024/09/25 02:50:07 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_table(t_table *table, char **av)
{
	t_philo			*philo;
	t_philo			*temp;

	philo = NULL;
	table->philo_num = ft_atoi(av[1]);
	pthread_mutex_init(&table->sim_mutex, NULL);
	table->fork_num = table->philo_num;
	int i = 0;
	while (i < table->philo_num)
	{
		temp = ft_lstnew(i);
		ft_lstadd_back(&philo, temp);
		i++;
	}
	temp = philo;//stupid fix
	while (philo->next != temp)//stupid fix
		philo = philo->next;//stupid fix
	table->philo = philo;
}

t_philo	*ft_lstnew(int counter)
{
	t_philo	*philo;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	
	pthread_mutex_init(&philo->fork, NULL);
	philo->id = counter + 1;//find better way to send id and ptid and stuff
	philo->ptid = 0;
	philo->next = NULL;
	philo->info.start_time = get_time(philo);
	
	//possibly unused
	philo->has_eaten = false;
	philo->has_slept = false;
	philo->info.time_to_die = 200;//av[2]
	philo->info.time_to_eat = 50;//av[3]
	philo->info.time_to_sleep = 100;//av[4]

	return (philo);
}

void	ft_lstadd_back(t_philo **lst, t_philo *to_add)
{
	static t_philo	*end;
	
	if (!lst)
		return ;
	if (!end)
	{
		*lst = to_add;
		to_add->next = *lst;
	}
	else
	{
		end->next = to_add;
		to_add->next = *lst;
	}
	end = to_add;
}


void	ft_lstclear(t_philo **philo)
{
	t_philo	*temp;
	t_philo	*first;

/* 	if (!philo)
		return ; */
	//destroy sim_mutex and fork mutex
	first = *philo;
	while (*philo)
	{
		temp = (*philo)->next;
		free(*philo);
		*philo = temp;
		if (*philo == first)
			break ;
	}
}
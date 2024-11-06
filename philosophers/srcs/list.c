/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 04:02:06 by bruno             #+#    #+#             */
/*   Updated: 2024/11/06 16:41:06 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_table(t_table *table, char **av)
{
	t_philo			*philo;
	t_philo			*temp;

	philo = NULL;
	int i = 0;
	while (i < ft_atoi(av[1]))
	{
		temp = ft_lstnew(i, av);
		temp->table = table;
		ft_lstadd_back(&philo, temp);
		i++;
	}
	table->philo = philo;
}

t_philo	*ft_lstnew(int counter, char **av)
{
	t_philo	*philo;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	
	pthread_mutex_init(&philo->fork, NULL);
	philo->id = counter + 1;
	philo->ptid = 0;
	philo->next = NULL;
	philo->info.time_die = ft_atoi(av[2]);//make this in parser?
	philo->info.time_eat = ft_atoi(av[3]);
	philo->info.time_sleep = ft_atoi(av[4]);

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
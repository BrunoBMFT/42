/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:48:45 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 00:49:18 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_lstclear(t_philo **philo)
{
	t_philo	*temp;
	t_philo	*first;

	if (!philo)
		return ;
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

t_philo	*ft_lstnew(int i, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf("alloc fail\n"), NULL);
	philo->id = i + 1;
	philo->ptid = 0;
	philo->next = NULL;
	philo->info.time_die = ft_atoi(av[2]);
	philo->info.time_eat = ft_atoi(av[3]);
	philo->info.time_sleep = ft_atoi(av[4]);
	philo->last_meal = get_time();
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	pthread_mutex_init(&philo->info.num_times_eat_mutex, NULL);
	philo->info.time_think = (philo->info.time_die
			- philo->info.time_eat - philo->info.time_sleep) / 4;
	if (av[5])
		philo->info.num_times_eat = ft_atoi(av[5]);
	else
		philo->info.num_times_eat = -1;
	return (philo);
}

void	single(t_philo *philo)
{
	printf("0 1 has taken a fork\n");
	usleep(philo->info.time_die * 1000);
	printf("%d 1 died\n", philo->info.time_die);
	ft_lstclear(&philo);
}

bool	init_table(t_table *table, char **av)
{
	t_philo			*philo;
	t_philo			*temp;
	int				i;

	i = 0;
	philo = NULL;
	table->start_time = get_time();
	table->initialized = 0;
	pthread_mutex_init(&table->is_running_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	while (i < ft_atoi(av[1]))
	{
		temp = ft_lstnew(i, av);
		if (!temp)
			return (ft_lstclear(&table->philo), false);
		temp->table = table;
		ft_lstadd_back(&philo, temp);
		i++;
		table->initialized++;
	}
	if (ft_atoi(av[1]) == 1)
		return (single(philo), false);
	table->philo = philo;
	table->philo_num = i;
	table->is_running = true;
	return (true);
}

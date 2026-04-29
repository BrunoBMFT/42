#include "./philosophers.h"

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

void	ft_lstadd_back(t_philo **lst, t_philo *new_philo)
{
	static t_philo	*end;

	if (!lst)
		return ;
	if (!end)
	{
		*lst = new_philo;
		new_philo->next = *lst;
	}
	else
	{
		end->next = new_philo;
		new_philo->next = *lst;
	}
	end = new_philo;
}

t_philo	*ft_lstnew(int i, char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (printf("Error!\nMalloc fail\n"), NULL);
	philo->id = i + 1;
	philo->ptid = 0;
	philo->next = NULL;
	philo->last_meal = get_time();
	philo->info.die_time = ft_atoi(av[2]);
	philo->info.eat_time = ft_atoi(av[3]);
	philo->info.sleep_time = ft_atoi(av[4]);
	philo->done_eating = 0;
	pthread_mutex_init(&philo->fork, NULL);
	pthread_mutex_init(&philo->mutex_last_meal, NULL);
	pthread_mutex_init(&philo->info.mutex_num_times_eat, NULL);
	philo->info.think_time = (philo->info.die_time
			- philo->info.eat_time - philo->info.sleep_time) / 4;
	if (av[5])
		philo->info.num_times_eat = ft_atoi(av[5]);
	else
		philo->info.num_times_eat = -1;
	return (philo);
}

int	ft_init_table(t_tab *table, char **av)
{
	t_philo			*philo;
	t_philo			*temp;
	int				i;

	i = 0;
	philo = NULL;
	table->start_time = get_time();
	pthread_mutex_init(&table->mutex_is_running, NULL);
	pthread_mutex_init(&table->mutex_print, NULL);
	while (i < ft_atoi(av[1]))
	{
		temp = ft_lstnew(i, av);
		if (!temp)
			return (ft_lstclear(&table->philo), 0);
		temp->table = table;
		ft_lstadd_back(&philo, temp);
		i++;
	}
	if (ft_atoi(av[1]) == 1)
		return (single(philo), 0);
	table->philo = philo;
	table->is_running = 1;
	table->all_done = 0;
	table->philo_num = i;
	return (1);
}

int	ft_init_philosophers(char **av, t_tab *table)
{
	if (!parse(av))
		return (0);
	if (!ft_init_table(table, av))
		return (0);
	return (1);
}

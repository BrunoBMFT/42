#include "./philosophers.h"

int	main(int argc, char **argv)
{
	t_philo	*first;
	t_tab	table;

	if (argc < 5 || argc > 6)
	{
		printf("Error.\nWrong number of arguments\n");
		return (0);
	}
	if (!ft_init_philosophers(argv, &table))
		return (0);
	first = table.philo;
	while (table.philo)
	{
		if (pthread_create(&table.philo->ptid, NULL,
				&philo_loop, table.philo))
			return (stop_philo(&table));
		table.philo = table.philo->next;
		if (table.philo == first)
			break ;
	}
	pthread_create(&table.monitor, NULL, &monitor_experiment, &table);
	join_all_threads(&table);
	return (0);
}

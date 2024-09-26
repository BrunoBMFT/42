
#include "../includes/philosophers.h"

int	get_time(t_philo *philo)
{
	int current_time;

	gettimeofday(&philo->info.time, 0);
	current_time = (philo->info.time.tv_sec * 1000) + (philo->info.time.tv_usec / 1000);
	return (current_time);
}

int	calculate_time(t_philo *philo)
{
	gettimeofday(&philo->info.time, 0);
	int	current_time = (philo->info.time.tv_sec * 1000) + (philo->info.time.tv_usec / 1000);
	current_time -= philo->info.start_time;
	return (current_time);
}

void	sleep_action(t_philo *philo)
{
	int	time_since_start = calculate_time(philo);
	print_sleeping(time_since_start, philo->id);
	philo->has_slept = true;
	usleep(philo->info.time_to_sleep * 1000);
}

void	think_action(t_philo *philo)
{
	int	time_since_start = calculate_time(philo);
	print_thinking(time_since_start, philo->id);
	//usleep not here because its waiting for a fork
}


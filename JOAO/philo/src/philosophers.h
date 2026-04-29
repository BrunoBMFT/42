#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>

enum actions {
	TOOKFORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_table	t_tab;

typedef struct s_info
{
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				die_time;
	int				num_times_eat;
	pthread_mutex_t	mutex_num_times_eat;
}				t_info;

typedef struct s_philo
{
	int				id;
	t_info			info;
	t_tab			*table;
	pthread_t		ptid;
	pthread_mutex_t	fork;
	pthread_mutex_t	mutex_last_meal;
	int				last_meal;
	int				done_eating;
	struct s_philo	*next;
}				t_philo;

struct			s_table
{
	t_philo			*philo;
	int				philo_num;
	int				all_done;
	int				is_running;
	pthread_t		monitor;
	pthread_mutex_t	mutex_is_running;
	pthread_mutex_t	mutex_print;
	int				start_time;
};

int		ft_is_digit(int c);
int		ft_is_even(int n);
long	ft_atol(const char *str);
int		ft_atoi(const char *str);
void	ft_lstclear(t_philo **philo);
int		ft_init_philosophers(char **av, t_tab *table);
int		parse(char **av);
void	*philo_loop(void *arg);
void	print_action(t_philo *philo, int action);
void	*monitor_experiment(void *tab);
int		died_while_waiting(t_philo *philo);
int		stop_philo(t_tab *table);
int		is_philo_running(t_tab *table);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
int		get_time(void);
void	join_all_threads(t_tab *table);
void	single(t_philo *philo);

#endif
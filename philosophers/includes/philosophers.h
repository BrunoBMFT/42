/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:49:43 by bruno             #+#    #+#             */
/*   Updated: 2024/11/27 00:49:35 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define TOOKFORK 1
# define EATING 2
# define SLEEPING 3
# define THINKING 4
# define DIED 5

typedef struct s_table	t_table;

typedef struct s_info
{
	int				time_eat;
	int				time_sleep;
	int				time_think;
	int				time_die;
	int				num_times_eat;
	pthread_mutex_t	num_times_eat_mutex;
}				t_info;

typedef struct s_philo
{
	int				id;
	t_table			*table;
	pthread_t		ptid;
	pthread_mutex_t	fork;
	int				last_meal;//since start of sim
	pthread_mutex_t	last_meal_mutex;
	t_info			info;
	struct s_philo	*next;
}				t_philo;

struct			s_table
{
	t_philo			*philo;
	int				philo_num;//maybe remove
	int				initialized;
	pthread_t		observer;
	bool			is_running;
	pthread_mutex_t	is_running_mutex;
	pthread_mutex_t	print_mutex;
	int				start_time;
};

//libft
int		ft_atoi(const char *str);
bool	ft_is_even(int n);
bool	ft_isdigit(int c);
long	ft_atol(const char *str);

//parser
bool	parser(int ac, char **av, t_table *table);
bool	init_table(t_table *table, char **av);

//philo
void	*philo_routine(void *arg);
void	print_action(t_philo *philo, int action);
void	*observe_experiment(void *tab);
bool	is_dead(t_philo *philo);
int		stop_sim(t_table *table);
bool	is_sim_running(t_table *table);


//mutex
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	set_int(pthread_mutex_t *mutex, int *to_set, int value);
void	set_bool(pthread_mutex_t *mutex, bool *to_set, bool value);
int		get_int(pthread_mutex_t *mutex, int from);
int		get_bool(pthread_mutex_t *mutex, bool from);
int		get_time(void);

//clean
void	ft_lstclear(t_philo **philo);
void	join_threads(t_table *table);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:49:43 by bruno             #+#    #+#             */
/*   Updated: 2024/11/06 16:46:13 by bruno            ###   ########.fr       */
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

typedef struct	s_info
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
	bool			status;
	pthread_mutex_t	status_mutex;
	pthread_mutex_t	print_mutex;
	int				start_time;
};


bool	parser(int ac, char **av);
bool	init_table(t_table *table, char **av);
void	join_threads(t_table *table);


void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
bool	is_sim_running(t_philo *philo);
void	stop_sim(t_philo *philo);
int		get_time(void);

bool		is_sim_running(t_philo *philo);

int	get_int(pthread_mutex_t *mutex, int from);
void	set_int(pthread_mutex_t *mutex, int *to_set, int value);
int	get_bool(pthread_mutex_t *mutex, bool from);
void	set_bool(pthread_mutex_t *mutex, bool *to_set, bool value);


void	print_action(t_philo *philo, int action);

//libft
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
bool	ft_isdigit(int c);
bool	ft_is_even(int n);
void	ft_lstclear(t_philo **philo);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:49:43 by bruno             #+#    #+#             */
/*   Updated: 2024/09/25 02:49:47 by bruno            ###   ########.fr       */
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

typedef struct s_info
{
	struct timeval	time;
	int				start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
//	int				num_times_eat;
}				t_info;


typedef struct s_philo
{
	int 			id;
 	pthread_t		ptid;
	pthread_mutex_t	fork;
	t_info			info;
	struct s_philo	*next;

	bool			has_eaten;//remove?
	bool			has_slept;//remove?
}				t_philo;

typedef struct s_table
{
	int				philo_num;//remove when possible
	int				fork_num;
	pthread_mutex_t	sim_mutex;
	t_philo			*philo;
}				t_table;


bool	parser(int ac, char **av);
int	ft_atoi(const char *str);
void	*start_philo(void *arg);
void	init_table(t_table *table, char **av);

//time
int	get_time(t_philo *philo);
int	calculate_time(t_philo *philo);

//action
void	sleep_action(t_philo *philo);
//void	eat_action(t_philo *philo);
void	think_action(t_philo *philo);

//logs
void	print_eating(int time, int philo);
void	print_tookfork(int time, int philo);
void	print_sleeping(int time, int philo);
void	print_thinking(int time, int philo);
void	print_died(int time, int philo);

//list
t_philo	*ft_lstnew(int counter);
void	ft_lstadd_back(t_philo **lst, t_philo *to_add);
void	ft_lstclear(t_philo **philo);


#endif
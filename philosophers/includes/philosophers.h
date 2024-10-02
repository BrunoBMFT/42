/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:49:43 by bruno             #+#    #+#             */
/*   Updated: 2024/10/02 02:43:53 by bruno            ###   ########.fr       */
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
	int				last_meal;
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
//have a table reference for each philo?
	struct s_philo	*next;

}				t_philo;

typedef struct s_table
{
	pthread_mutex_t	sim_mutex;
	t_philo			*philo;
}				t_table;


bool	parser(int ac, char **av);
int		ft_atoi(const char *str);
void	*start_philo(void *arg);
void	init_table(t_table *table, char **av);

//time
int	get_current_time(t_philo *philo);
int	time_since_start(t_philo *philo);
int	time_since_last(t_philo *philo);

void	lock(t_philo *philo);
void	unlock(t_philo *philo);

//action
/* void	sleep_action(t_philo *philo);
void	eat_action(t_philo *philo);
void	think_action(t_philo *philo); */


void	print_action(t_philo *philo, int action);

//list
t_philo	*ft_lstnew(int counter, char **av);
void	ft_lstadd_back(t_philo **lst, t_philo *to_add);
void	ft_lstclear(t_philo **philo);


#endif
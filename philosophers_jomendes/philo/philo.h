/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:29:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/07 12:37:31 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo	t_philo;
typedef struct s_info	t_info;

typedef struct s_fork
{
	int					available;
	pthread_mutex_t		mutex;
}						t_fork;

struct					s_info
{
	int					n_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_meals;
	unsigned long		start_time;
	int					dead;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		lock;
	pthread_mutex_t		message;
};

struct					s_philo
{
	int					id;
	pthread_t			thread;
	int					meals_counter;
	unsigned long		time_to_die;
	pthread_mutex_t		meal_mutex;
	t_fork				*r_fork;
	t_fork				*l_fork;
	t_info				*info;
};

// utils.c

int						check_args(char **av);
int						ft_atol(char *str);
unsigned long			get_time(unsigned long start_time);
int						check_for_values(t_info *info);

// init.c

void					init_forks(t_info *info);
int						init_program(char **av, t_info *info);
void					run_program(t_info *info);
void					finish_program(t_info *info);

// actions.c		

int						is_dead(t_philo *philo);
int						start_sleeping(t_philo *philo);
int						start_eating(t_philo *philo);
void					start_thinking(t_philo *philo);

// forks.c		

int						try_eat_even(t_philo *philo);
int						try_eat_odd(t_philo *philo);
int						are_forks_available(t_philo *philo);
void					grab_forks(t_philo *philo);
void					release_forks(t_philo *philo);

// philo.c

int						special_case(t_philo *philo);
int						exec_routine(t_philo *philo);
void					*routine(void *philo_pointer);

#endif
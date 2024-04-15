/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:28:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/15 22:59:51 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/types.h>
# include <limits.h>

# define PHILOS_MAX 200

typedef struct s_fork
{
	pthread_mutex_t	fork;
}		t_fork;

typedef struct s_info
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_meals_to_eat;
	bool			stop_sim;
	pthread_mutex_t	sim;
	pthread_mutex_t	print;
}		t_info;

typedef struct s_philo
{
	int				id;
	int				n_meals_eaten;
	bool			is_dead;
	bool			is_full;
	suseconds_t		time_last_meal;
	suseconds_t		time_start_routine;
	pthread_t		philo_thread;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_info			*info;
}		t_philo;

typedef struct s_table
{
	t_info			info;
	pthread_t		monitor_thread;
	t_philo			philos[PHILOS_MAX];
	t_fork			forks[PHILOS_MAX];
}		t_table;

//error_check
void		check_argv(char **argv);
//init & cleanup
void		init(t_table *table, char **argv);
void		destroy_info_mutexes(t_table *table);
void		cleanup(t_table *table);
//simulation
void		simulation(t_table *table);
void		*routine(void *arg);
void		*monitor(void *arg);
//events
void		print_action(t_philo *philo, char *str);
void		eat(t_philo *philo);
//utils
suseconds_t	get_time_ms(void);
long		ft_atol(const char *s);
void		ft_error(char *error_msg);
void		precise_usleep(long milliseconds);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 18:28:59 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:37:02 by fwahl            ###   ########.fr       */
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
void		check_input(int argc, char **argv);
//init
void		init(t_table *table, char **argv);
//simulation
void		start_philo_threads(t_table *table);
void		join_philo_threads(t_table *table);
void		start_monitor_thread(t_table *table);
void		join_monitor_thread(t_table *table);
void		one_philo(t_table *table);
void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

//utils
bool		ft_isspace(char c);
bool		ft_isdigit(char c);
long		ft_atol(const char *s);
void		ft_error(char *error_msg);
void		print_action(t_philo *philo, char *str);
void		precise_usleep(long milliseconds);
void		ft_mutex_destroy(t_table *table);
suseconds_t	get_time_ms(void);

#endif

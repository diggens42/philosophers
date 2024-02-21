/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:29:17 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/21 20:24:25 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_table t_table;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			time_last_meal;
	bool			is_full;
	bool			is_deadge;
	pthread_t		thread;
	t_table			*table;
	t_fork			*fork_right;
	t_fork			*fork_left;	
}	t_philo;

typedef struct s_table
{
	long			amount_philo;	//av[1]
	long			max_meals;		//av[5]
	suseconds_t		time_to_die;	//av[2]
	suseconds_t		time_to_eat;	//av[3]
	suseconds_t		time_to_sleep;	//av[4]
	suseconds_t		start;
	bool			stop;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_t		overseer;
	t_fork			*forks;
	t_philo			*philos;
}	t_table;

//ft
void	check_input(char **argv);
void	init(t_table *table, char **argv);
void	start_sim(t_table *table);
void	eat(t_philo *philo);
void	print_action(t_philo *philo, char *str);
void	take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);

//util
void	ft_error(char *error_msg);
long	ft_atol(const char *s);
bool	ft_isspace(char c);
bool	ft_isdigit(char c);
long	get_time_ms(void);
long	get_time_us(void);

#endif
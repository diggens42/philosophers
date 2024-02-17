/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:29:17 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/17 18:12:16 by fwahl            ###   ########.fr       */
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
#include <limits.h>

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				id;
}	t_fork;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		time_last_meal;
	bool		is_full;
	pthread_t	thread_num;
	t_fork		*fork_right;
	t_fork		*fork_left;	
}	t_philo;

typedef struct s_table
{
	long	amount_philo;	//av[1]
	long	time_to_die;	//av[2]
	long	time_to_eat;	//av[3]
	long	time_to_sleep;	//av[4]
	long	meals_max;		//av[5]
	bool	stop;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

//ft
void	check_input(char **argv);
void	init(t_table *table, char **argv);

//util
void	ft_error(char *error_msg);
long	ft_atol(const char *s);
bool	ft_isspace(char c);
bool	ft_isdigit(char c);

#endif
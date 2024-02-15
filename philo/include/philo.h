/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:29:17 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/15 20:24:34 by fwahl            ###   ########.fr       */
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
	long	amount_philo;
	long	meals_max;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

//ft
void	check_input(char **argv);

//util
void	ft_error(char **str);
long	ft_atol(const char *s);

#endif
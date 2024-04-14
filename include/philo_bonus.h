/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:20:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/14 21:51:31 by fwahl            ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>

#define PHILOS_MAX 200

typedef struct s_info
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_meals_to_eat;
	bool			stop_sim;
}		t_info;

typedef struct s_philo
{
	int				id;
	int				n_meals_eaten; //This might need to be tracked differently if required across processes
	bool			is_dead;    //Difficult to manage without shared memory, consider design implications
	bool			is_full; //Difficult to manage without shared memory, consider design implications
	suseconds_t		time_last_meal;
	suseconds_t		time_start_routine;
	t_info			*info;
}		t_philo;

typedef struct s_table
{
	t_info			info;
	t_philo			philos[PHILOS_MAX];
	sem_t			forks[PHILOS_MAX];
}		t_table;

void	init_bonus(t_table *table, char **argv);

#endif

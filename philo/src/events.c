/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 20:51:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/20 21:25:39 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_action(t_philo *philo, char *str)
{
	suseconds_t	time;

	pthread_mutex_lock(philo->table->print);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(philo->table->print);
		return ;
	}
	time = get_time_ms() - philo->table->start;
	printf("%d Philo %d %s ", time, philo->id, str);
	pthread_mutex_unlock(philo->table->print);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->fork_left->fork);
		print_action(philo, "takes the left fork");
		pthread_mutex_lock(philo->fork_right->fork);
		print_action(philo, "takes the right fork");
	}
	else
	{
		pthread_mutex_lock(philo->fork_right->fork);
		print_action(philo, "takes the right fork");
		pthread_mutex_lock(philo->fork_left->fork);
		print_action(philo, "takes the left fork");
	}
}

void	drop_forks(t_philo *philo)
{
		if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(philo->fork_left->fork);
		print_action(philo, "drops the left fork");
		pthread_mutex_unlock(philo->fork_right->fork);
		print_action(philo, "drops the right fork");
	}
	else
	{
		pthread_mutex_unlock(philo->fork_right->fork);
		print_action(philo, "drops the right fork");
		pthread_mutex_unlock(philo->fork_left->fork);
		print_action(philo, "drops the left fork");
	}
}

void	eat(t_philo *philo)
{	
	take_forks(philo);
	pthread_mutex_lock(philo->table->eat);
	philo->time_last_meal = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->table->eat);
	print_action(philo, "is eating");
	usleep(philo->table->time_to_eat);
	drop_forks(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 00:03:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:08:26 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_full(t_philo *philo)
{
	if (philo->info->n_meals_to_eat > 0
		&& philo->n_meals_eaten >= philo->info->n_meals_to_eat)
		return (true);
	return (false);
}

static void	take_forks_even(t_philo *philo)
{
	// if (philo->id % 2 == 0)
	// 	usleep(150);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork\n");
}

static void take_forks_odd(t_philo *philo)
{
	if (philo->id == philo->info->n_philos)
		usleep(10);
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork\n");
	}
}

static void	take_forks(t_philo *philo)
{
	if (philo->info->n_philos % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->sim);
	if (philo->info->stop_sim)
	{
		pthread_mutex_unlock(&philo->info->sim);
		return ;
	}
	pthread_mutex_unlock(&philo->info->sim);
	take_forks(philo);
	print_action(philo, "is eating\n");
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal);
	philo->n_meals_eaten++;
	if (philo->is_full == false)
		philo->is_full = is_full(philo);
	precise_usleep(philo->info->time_to_eat);
	drop_forks(philo);
}

void	print_action(t_philo *philo, char *str)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->stop_sim == true)
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	time = get_time_ms() - philo->time_start_routine;
	printf("%d Philo %d %s ", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
}

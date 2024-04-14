/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 00:03:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/17 20:38:14 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	is_full(t_philo *philo)
{
	if (philo->info->n_meals_to_eat > 0
		&& philo->n_meals_eaten >= philo->info->n_meals_to_eat)
	{
		// philo->is_full = true;
		print_action(philo, "is full\n");
		pthread_mutex_lock(&philo->info->full);
		philo->info->n_philos_full++;
		pthread_mutex_unlock(&philo->info->full);
		return (true);
	}
	return (false);
}

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 != 0)
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

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
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
	pthread_mutex_lock(&philo->info->eat);
	print_action(philo, "is eating\n");
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->last_meal);
	philo->n_meals_eaten++;
	philo->is_full = is_full(philo);
	pthread_mutex_unlock(&philo->info->eat);
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

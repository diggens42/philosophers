/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:42:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:52:20 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	print_action(t_philo *philo, char *str)
{
	suseconds_t	time;

	sem_wait(philo->info->print);
	if (philo->info->stop_sim == true)
	{
		sem_post(philo->info->print);
		return ;
	}
	time = get_time_ms() - philo->time_start_routine;
	printf("%d Philo %d %s ", time, philo->id, str);
	sem_post(philo->info->print);
}

static void take_forks(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	sem_wait(philo->last_meal);
	philo->time_last_meal = get_time_ms();
	sem_post(philo->last_meal);
	print_action(philo, "is eating");
	precise_usleep(philo->info->time_to_eat);
	philo->n_meals_eaten++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_forks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:42:26 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 23:57:33 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks_odd(t_philo *philo)
{
	usleep(50);
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
}

static void	take_forks_even(t_philo *philo)
{
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	print_action(philo, "has taken a fork");
}

void	take_forks(t_philo *philo)
{
	if (philo->info->n_philos % 2 == 0)
		take_forks_even(philo);
	else
		take_forks_odd(philo);
}

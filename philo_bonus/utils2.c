/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:11:01 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 20:03:34 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *error_msg)
{
	ft_sem_unlink();
	printf("Error: %s", error_msg);
	exit(EXIT_FAILURE);
}

void	ft_sem_unlink(void)
{
	sem_unlink("/print");
	sem_unlink("/sim");
	sem_unlink("/last_meal");
	sem_unlink("/forks");
}

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

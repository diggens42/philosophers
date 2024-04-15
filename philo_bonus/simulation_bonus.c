/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:13:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:48:10 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


static void	philo_routine(t_philo *philo)
{
	while (!philo->info->stop_sim)
	{
		eat(philo);
		print_action(philo, "is sleeping");
		precise_usleep(philo->info->time_to_sleep);
		print_action(philo, "is thinking");
	}
}

void	simulation_bonus(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < table->info.n_philos)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_routine(&table->philos[i]);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
			ft_error("fork error");
		i++;
	}
	monitor_thread(table);
	i = 0;
	while (i < table->info.n_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:13:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:07:36 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

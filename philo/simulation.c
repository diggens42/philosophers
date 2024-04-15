/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:56:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:19:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	start_philo_threads(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		philo->time_last_meal = get_time_ms();
		philo->time_start_routine = get_time_ms();
		if (pthread_create(&philo->philo_thread, NULL, routine, philo) != 0)
		{
			ft_error("Failed thread creation for philo\n");
			while (j < i)
			{
				pthread_join(table->philos[j].philo_thread, NULL);
				j++;
			}
			cleanup(table);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	join_philo_threads(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		pthread_join(philo->philo_thread, NULL);
		i++;
	}
}

static void	start_monitor_thread(t_table *table)
{
	if (pthread_create(&table->monitor_thread, NULL, monitor, table) != 0)
	{
		ft_error("failed thread creation for monitor");
		join_philo_threads(table);
		cleanup(table);
		exit(EXIT_FAILURE);
	}
}

static void	join_monitor_thread(t_table *table)
{
	pthread_join(table->monitor_thread, NULL);
}

void	simulation(t_table *table)
{
	start_philo_threads(table);
	start_monitor_thread(table);
	join_philo_threads(table);
	join_monitor_thread(table);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:40:10 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 20:35:20 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	stop_simulation(t_table *table)
{
	bool	all_philos_full;
	int		i;
	t_philo	*philo;

	all_philos_full = true;
	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		sem_wait(philo->last_meal);
		if (get_time_ms() - philo->time_last_meal > table->info.time_to_die)
		{
			sem_post(philo->last_meal);
			return (true);
		}
		sem_post(philo->last_meal);
		if (table->info.n_meals_to_eat > 0
				&& philo->n_meals_eaten < table->info.n_meals_to_eat)
			all_philos_full = false;
		i++;
	}
	if (table->info.n_meals_to_eat > 0 && all_philos_full == true)
		return (true);
	return (false);
}

static void *monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (true)
	{
		if (stop_simulation(table))
		{
			sem_wait(table->info.sim);
			table->info.stop_sim = true;
			sem_post(table->info.sim);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}

void	start_monitor_thread(t_table *table)
{
	pthread_t	monitor_thread;

	monitor_thread = NULL;
	if (pthread_create(&monitor_thread, NULL, monitor, table) != 0)
		ft_error("error creating monitor thread");
	if (pthread_detach(monitor_thread) != 0)
		ft_error("error detaching monitor thread");
}

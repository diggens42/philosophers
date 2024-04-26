/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:57:14 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:53:32 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_death(t_table *table)
{
	int			i;
	suseconds_t	diff;

	i = 0;
	while (i < table->info.n_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_meal);
		diff = get_time_ms() - table->philos[i].time_last_meal;
		pthread_mutex_unlock(&table->philos[i].last_meal);
		if (diff > table->info.time_to_die)
		{
			print_action(&table->philos[i], "has died");
			pthread_mutex_lock(&table->info.sim);
			table->info.stop_sim = true;
			pthread_mutex_unlock(&table->info.sim);
			break ;
		}
		i++;
	}
}

static void	check_full(t_table *table)
{
	int		philos_full;
	int		i;

	philos_full = 0;
	i = 0;
	while (i < table->info.n_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_meal);
		if (table->philos[i].is_full == true)
			philos_full++;
		pthread_mutex_unlock(&table->philos[i].last_meal);
		i++;
	}
	if (philos_full == table->info.n_philos)
	{
		pthread_mutex_lock(&table->info.print);
		printf("All Philos are full!\n");
		pthread_mutex_unlock(&table->info.print);
		pthread_mutex_lock(&table->info.sim);
		table->info.stop_sim = true;
		pthread_mutex_unlock(&table->info.sim);
	}
}

static void	*monitor(void *arg)
{
	t_table	*table;
	bool	stop;

	table = (t_table *)arg;
	stop = false;
	while (true)
	{
		check_death(table);
		pthread_mutex_lock(&table->info.sim);
		stop = table->info.stop_sim;
		pthread_mutex_unlock(&table->info.sim);
		if (stop)
			break ;
		check_full(table);
		pthread_mutex_lock(&table->info.sim);
		stop = table->info.stop_sim;
		pthread_mutex_unlock(&table->info.sim);
		if (stop)
			break ;
	}
	return (NULL);
}

void	start_monitor_thread(t_table *table)
{
	if (pthread_create(&table->monitor_thread, NULL, monitor, table) != 0)
	{
		ft_error("failed thread creation for monitor");
		join_philo_threads(table);
		ft_mutex_destroy(table);
		exit(EXIT_FAILURE);
	}
}

void	join_monitor_thread(t_table *table)
{
	pthread_join(table->monitor_thread, NULL);
}

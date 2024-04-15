/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 22:40:23 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/15 21:06:47 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

static void	check_death(t_table *table)
{
	int			i;
	bool		philo_dead;
	suseconds_t	diff;

	philo_dead = false;
	i = 0;
	while (i < table->info.n_philos)
	{
		pthread_mutex_lock(&table->philos[i].last_meal);
		diff = get_time_ms() - table->philos[i].time_last_meal;
		pthread_mutex_unlock(&table->philos[i].last_meal);
		if (diff > table->info.time_to_die)
		{
			print_action(&table->philos[i], "has died\n");
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
		if (table->philos[i].is_full == true)
			philos_full++;
		i++;
	}
	if (philos_full == table->info.n_philos)
	{
		pthread_mutex_lock(&table->info.sim);
		table->info.stop_sim = true;
		pthread_mutex_unlock(&table->info.sim);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0 && philo->info->n_philos % 2 == 0)
		precise_usleep(10);
	while (!philo->info->stop_sim)
	{
		eat(philo);
		print_action(philo, "is sleeping\n");
		precise_usleep(philo->info->time_to_sleep);
		print_action(philo, "is thinking\n");
	}
	return (NULL);
}

void	*monitor(void *arg)
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

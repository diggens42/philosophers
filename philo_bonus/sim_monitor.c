/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_monitor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:40:10 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:25:00 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	check_death(t_philo	*philo)
{
	suseconds_t	time;

	sem_wait(philo->last_meal);
	if (get_time_ms() - philo->time_last_meal > philo->info->time_to_die)
	{
		sem_wait(philo->info->print);
		time = get_time_ms() - philo->time_start_routine;
		printf("%d Philo %d has died\n", time, philo->id);
		sem_post(philo->last_meal);
		return (true);
	}
	sem_post(philo->last_meal);
	return (false);
}

static void *dead_monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->info->sim);
		if (check_death(philo))
		{
			sem_post(philo->info->sim);
			exit(EXIT_SUCCESS);
		}
		sem_post(philo->info->sim);
	}
	return (NULL);
}

void	start_death_check(t_philo *philo)
{
	pthread_t	deadge;

	philo->time_last_meal = get_time_ms();
	philo->time_start_routine = get_time_ms();
	if (pthread_create(&deadge, NULL, dead_monitor, philo) != 0)
		ft_error("error creating monitor thread");
	if (pthread_detach(deadge) != 0)
		ft_error("error detaching monitor thread");
}

static void *full_monitor(void *arg)
{
	t_table	*table;
	int		philos_full;
	int		i;

	table = (t_table *)arg;
	philos_full = 0;
	while (philos_full < table->info.n_philos + 1)
	{
		sem_wait(table->info.full);
		philos_full++;
	}
	sem_wait(table->info.print);
	if (philos_full >= table->info.n_philos)
	{
		printf("All Philos are full!");
		i = 0;
		while (i < table->info.n_philos)
		{
			sem_wait(table->info.pid);
			kill(table->philos[i].pid, SIGTERM);
			sem_post(table->info.pid);
			i++;
		}
	}
	return (NULL);
}

void	start_full_check(t_table *table)
{
	pthread_t	full;

	if (pthread_create(&full, NULL, full_monitor, table) != 0)
		ft_error("error creating monitor thread");
	if (pthread_detach(full) != 0)
		ft_error("error detaching monitor thread");

}

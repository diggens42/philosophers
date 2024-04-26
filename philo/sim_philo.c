/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:01:49 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:53:56 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->sim);
	if (philo->info->stop_sim)
	{
		pthread_mutex_unlock(&philo->info->sim);
		return ;
	}
	pthread_mutex_unlock(&philo->info->sim);
	take_forks(philo);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal);
	philo->time_last_meal = get_time_ms();
	philo->n_meals_eaten++;
	if (philo->is_full == false)
		if (philo->info->n_meals_to_eat > 0
			&& philo->n_meals_eaten >= philo->info->n_meals_to_eat)
			philo->is_full = true;
	pthread_mutex_unlock(&philo->last_meal);
	precise_usleep(philo->info->time_to_eat);
	drop_forks(philo);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_usleep(10);
	while (true)
	{
		pthread_mutex_lock(&philo->info->sim);
		if (philo->info->stop_sim)
		{
			pthread_mutex_unlock(&philo->info->sim);
			break ;
		}
		pthread_mutex_unlock(&philo->info->sim);
		eat(philo);
		print_action(philo, "is sleeping");
		precise_usleep(philo->info->time_to_sleep);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

void	one_philo(t_table *table)
{
	t_philo	*philo;

	philo = &table->philos[0];
	philo->time_last_meal = get_time_ms();
	philo->time_start_routine = get_time_ms();
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	precise_usleep(table->info.time_to_die);
	print_action(philo, "has died");
	pthread_mutex_unlock(philo->left_fork);
}

void	start_philo_threads(t_table *table)
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
			ft_mutex_destroy(table);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	join_philo_threads(t_table *table)
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

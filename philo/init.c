/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:24:25 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:52:53 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_info(t_table *table, char **argv)
{
	t_info	*info;

	info = &table->info;
	info->n_philos = ft_atol(argv[1]);
	info->time_to_die = ft_atol(argv[2]);
	info->time_to_eat = ft_atol(argv[3]);
	info->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		info->n_meals_to_eat = ft_atol(argv[5]);
	else
		info->n_meals_to_eat = -42;
	if (info->n_philos <= 0 || info->n_philos > 200)
		ft_error("invalid amount of philos");
	if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_sleep < 60)
		ft_error("time to die/eat/sleep must be more than 60ms");
	info->stop_sim = false;
	if (pthread_mutex_init(&info->sim, NULL) != 0)
		ft_error("error sim mutex init");
	if (pthread_mutex_init(&info->print, NULL) != 0)
	{
		pthread_mutex_destroy(&info->sim);
		ft_error("error print mutex init");
	}
}

static void	init_last_meal_mutex(t_table *table, int i)
{
	int	j;

	j = 0;
	if (pthread_mutex_init(&table->philos[i].last_meal, NULL) != 0)
	{
		while (j < table->info.n_philos)
		{
			pthread_mutex_destroy(&table->forks[j].fork);
			if (j < i)
				pthread_mutex_destroy(&table->philos[j].last_meal);
			j++;
		}
		pthread_mutex_destroy(&table->info.sim);
		pthread_mutex_destroy(&table->info.print);
		ft_error("error last meal mutex init");
	}
}

static void	init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->n_meals_eaten = 0;
		philo->is_dead = false;
		philo->is_full = false;
		philo->info = &table->info;
		philo->left_fork = &table->forks[(i) % table->info.n_philos].fork;
		philo->right_fork = &table->forks[(i + 1) % table->info.n_philos].fork;
		init_last_meal_mutex(table, i);
		i++;
	}
}

static void	init_forks(t_table *table)
{
	t_fork	*fork;
	int		i;

	i = 0;
	while (i < table->info.n_philos)
	{
		fork = &table->forks[i];
		if (pthread_mutex_init(&fork->fork, NULL) != 0)
		{
			pthread_mutex_destroy(&table->info.sim);
			pthread_mutex_destroy(&table->info.print);
			ft_error("error fork mutex init");
		}
		i++;
	}
}

void	init(t_table *table, char **argv)
{
	init_info(table, argv);
	init_forks(table);
	init_philo(table);
}

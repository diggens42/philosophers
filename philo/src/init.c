/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:07:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/21 20:25:20 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_table(t_table *table, char **argv)
{
	table->amount_philo = ft_atol(argv[1]);
	table->time_to_die = (suseconds_t)ft_atol(argv[2]) * 1000;
	table->time_to_eat = (suseconds_t)ft_atol(argv[3]) * 1000;
	table->time_to_sleep = (suseconds_t)ft_atol(argv[4]) * 1000;
	if (argv[5] != NULL)
		table->max_meals = ft_atol(argv[5]);
	else
		table->max_meals = -1;
	if (table->amount_philo <= 0 || table->amount_philo > 200)
		ft_error("Number of philos must be between 1 and 200");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000 
		|| table->time_to_sleep < 60000)
		ft_error("Time to die/eat/sleep more than 60ms");
	table->stop = false;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->amount_philo);
	// 	//catch malloc error
	table->forks = (t_fork *)malloc(sizeof(t_fork) * table->amount_philo);
	// 	//catch malloc error
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->eat, NULL);
}

static void init_philos(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->amount_philo)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->meals_eaten = 0;
		philo->time_last_meal = get_time_ms();
		philo->is_full = false;
		philo->table = table;
		i++;
	}
}

static void init_forks(t_table *table)
{
	t_philo	*philo;
	int		i;
		
	i = 0;
	while (i < table->amount_philo)
	{
		pthread_mutex_init(&table->forks[i].fork, NULL);
		table->forks[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < table->amount_philo)
	{
		philo = &table->philos[i];
		philo->fork_right = &table->forks[i];
		if (i == 0)
			philo->fork_left = &table->forks[table->amount_philo - 1];
		else
			philo->fork_left = &table->forks[i - 1];
		i++;
	}
}

void	init(t_table *table, char **argv)
{
	init_table(table, argv);
	init_philos(table);
	init_forks(table);
}

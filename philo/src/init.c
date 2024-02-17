/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:07:09 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/17 18:39:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_table(t_table *table, char **argv)
{
	table->amount_philo = ft_atol(argv[1]);
	table->forks = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1000;
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		table->meals_max = ft_atol(argv[5]);
	else
		table->meals_max = -1;
	if (table->amount_philo <= 0 || table->amount_philo > 200)
		ft_error("Number of philos must be between 1 and 200");
	if (table->time_to_die < 60000 || table->time_to_eat < 60000 
		|| table->time_to_sleep < 60000)
		ft_error("Time to die/eat/sleep more than 60ms");
	table->stop = false;
	table->philos = malloc(sizeof(t_philo) * table->amount_philo);
		//catch malloc error
	table->forks = malloc(sizeof(t_fork) * table->amount_philo);
		//catch malloc error

}

static void init_philos(t_table *table)
{
	// t_philo	*philo;
	int		i;

	i = 0;
	while (i < table->amount_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].time_last_meal = 0;
		table->philos[i].is_full = false;
		i++;
	}
}

static void init_forks(t_table *table)
{
	int	i;
	
	i = 0;
	while (i < table->amount_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		table->forks[i].id = i + 1;
		if (i == 0)
			table->philos[i].fork_right = &table->forks[i];
		else if (i == table->amount_philo - 1)
		{
			table->philos[0].fork_left = &table->forks[table->amount_philo - 1];
			table->philos[i].fork_left = &table->forks[i - 1];
			table->philos[i].fork_right = &table->forks[i];
		}
		else
		{
			table->philos[i].fork_left = &table->forks[i - 1];
			table->philos[i].fork_right = &table->forks[i];
		}
		i++;
	}
}

void	init(t_table *table, char **argv)
{
	init_table(table, argv);
	init_philos(table);
	init_forks(table);
}

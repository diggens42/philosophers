/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:30 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/15 22:49:41 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

static void	init_info_bonus(t_table *table, char **argv)
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
}

static void	init_philo_bonus(t_table *table)
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
		i++;
	}
}

static void	init_forks_bonus(t_table *table)
{
	table->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, table->info.n_philos);
	if (table->forks == SEM_FAILED)
	{
		sem_unlink("/forks");
		ft_error("sem_open error");
		exit(EXIT_FAILURE);
	}
}


void	init_bonus(t_table *table, char **argv)
{
	init_info_bonus(table, argv);
	init_philo_bonus(table);
	init_forks_bonus(table);
}

void	cleanup_semaphores(void)
{
	sem_unlink("/forks");
}

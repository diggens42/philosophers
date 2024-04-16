/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:30 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 21:21:50 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static sem_t *ft_sem_open(char *name, int amount)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, amount);
	if (sem == SEM_FAILED)
		ft_error("error sem_open");
	return (sem);
}

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
	info->sim = ft_sem_open("sim", 1);
	printf("test1\n");
	info->print = ft_sem_open("print", 1);
	printf("test2\n");
	info->forks = ft_sem_open("forks", info->n_philos);
	printf("test3\n");
}

static void	init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;
	char	last_meal_name[16];

	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->n_meals_eaten = 0;
		// philo->is_dead = false;
		// philo->is_full = false;
		philo->info = &table->info;
		philo->last_meal = ft_sem_open("last_meal", 1);
		i++;
	}
}

void	init(t_table *table, char **argv)
{
	init_info(table, argv);
	init_philo(table);
}

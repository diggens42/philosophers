/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:44:30 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/17 02:12:45 by fwahl            ###   ########.fr       */
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
	info->start = ft_sem_open("start", 0);
	info->start = ft_sem_open("full", 1);
	info->print = ft_sem_open("print", 1);
	info->forks = ft_sem_open("forks", info->n_philos);
}

static void	init_philo(t_table *table)
{
	t_philo	*philo;
	int		i;
	char	*temp;

	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		philo->id = i + 1;
		philo->n_meals_eaten = 0;
		philo->info = &table->info;
		ft_strlcpy(philo->last_meal_name, "last_meal_", sizeof(philo->last_meal_name));
		temp = ft_itoa(philo->id);
		ft_strlcat(philo->last_meal_name, temp, sizeof(philo->last_meal_name));
		free(temp);
		philo->last_meal = ft_sem_open(philo->last_meal_name, 1);
		i++;
	}
}

void	init(t_table *table, char **argv)
{
	init_info(table, argv);
	init_philo(table);
}

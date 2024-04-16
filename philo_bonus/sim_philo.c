/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:13:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 22:54:15 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *philo)
{
	take_forks(philo);
	sem_wait(philo->last_meal);
	philo->time_last_meal = get_time_ms();
	sem_post(philo->last_meal);
	print_action(philo, "is eating");
	precise_usleep(philo->info->time_to_eat);
	philo->n_meals_eaten++;
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->info->n_philos % 2 == 0)
		precise_usleep(10);
	while (!philo->info->stop_sim)
	{
		eat(philo);
		print_action(philo, "is sleeping");
		precise_usleep(philo->info->time_to_sleep);
		print_action(philo, "is thinking");
	}
}

void	fork_philo_process(t_table *table)
{
	t_philo	*philo;
	pid_t	pid;
	int		i;

	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		philo->time_last_meal = get_time_ms();
		philo->time_start_routine = get_time_ms();
		pid = fork();
		if (pid == 0)
		{
			philo_routine(philo);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0)
			ft_error("fork error");
		i++;
	}
}

void wait_philo_process(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->info.n_philos)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}


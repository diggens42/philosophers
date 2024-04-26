/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:13:12 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:39:54 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_philo *philo)
{
	sem_wait(philo->info->sim);
	if (philo->info->stop_sim)
	{
		sem_post(philo->info->sim);
		return ;
	}
	sem_post(philo->info->sim);
	take_forks(philo);
	sem_wait(philo->last_meal);
	philo->time_last_meal = get_time_ms();
	sem_post(philo->last_meal);
	print_action(philo, "is eating");
	precise_usleep(philo->info->time_to_eat);
	philo->n_meals_eaten++;
	if (philo->n_meals_eaten == philo->info->n_meals_to_eat)
		sem_post(philo->info->full);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

static void	philo_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		precise_usleep(10);
	while (!philo->info->stop_sim)
	{
		eat(philo);
		if (philo->info->stop_sim)
			return ;
		print_action(philo, "is sleeping");
		precise_usleep(philo->info->time_to_sleep);
		print_action(philo, "is thinking");
	}
}

void	one_philo(t_table *table)
{
	t_philo	*philo;

	philo = &table->philos[0];
	philo->time_last_meal = get_time_ms();
	philo->time_start_routine = get_time_ms();
	sem_wait(table->info.forks);
	print_action(philo, "has taken a fork");
	precise_usleep(table->info.time_to_die);
	print_action(philo, "has died");
	sem_post(table->info.forks);
}

void	fork_philo_process(t_table *table)
{
	t_philo	*philo;
	int		i;

	if (table->info.n_meals_to_eat != -42)
		start_full_check(table);
	i = 0;
	while (i < table->info.n_philos)
	{
		philo = &table->philos[i];
		sem_wait(table->info.pid);
		philo->pid = fork();
		sem_post(table->info.pid);
		if (philo->pid == 0)
		{
			sem_wait(table->info.start);
			start_death_check(philo);
			philo_routine(philo);
			exit(EXIT_SUCCESS);
		}
		else if (philo->pid < 0)
			ft_error("fork error");
		i++;
	}
	i = 0;
	while(i < table->info.n_philos)
	{
		sem_post(table->info.start);
		i++;
	}
}

void wait_philo_process(t_table *table)
{
	t_philo	*philo;
	int 	exit_status;
	int		i;

	waitpid(-1, &exit_status, 0);
	if (WIFEXITED(exit_status))
	{
		i = 0;
		while (i < table->info.n_philos)
		{
			philo = &table->philos[i];
			sem_wait(table->info.pid);
			kill(philo->pid, SIGTERM);
			sem_post(table->info.pid);
			i++;
		}
	}
}


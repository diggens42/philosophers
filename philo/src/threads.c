/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:24:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/21 21:16:21 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
// thread: pointer to a pthread_t variable where thread ID will be stores after the thread is created
// attr: optional pointer to pthread_attr_t struct that allows you to specify various attributes for thread, such as stack size, schedulign policy etc. (USE NULL FOR DEFAULT ATTRIBUTES)
// start_routine: function pointer to the fucntion that will be executed by the new thread. takes void* and returns void*. entry point for the new thread
// arg: pointer to the arg that will be passed to start_Routine when thread is created.

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *) arg;
	while (philo->table->stop == false)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_action(philo, "is sleeping");
		usleep(philo->table->time_to_sleep);
		print_action(philo, "thinking");
	}
	return (NULL); // ?
}

void	*overseer_routine(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	int		i;
	int		philos_full;
	
	while (1)
	{	
		i = 0;
		philos_full = 0;
		while(&philos[i] != NULL)
		{
			if (philos->is_full == true)
				philos_full++;
			if (philos->is_deadge == true)
				philos->table->stop = true;
			i++;
		}
		if (philos_full == philos[0].table->amount_philo)
			philos[0].table->stop = true;
		if (philos[0].table->stop == true)
			exit(EXIT_SUCCESS);
		
	}
}

void	start_sim(t_table *table)
{
	t_philo *philo;
	int	i;
	
	i = 0;
	pthread_create(&table->overseer, NULL, &overseer_routine, table->philos);
	if (table->max_meals == 0)
		return ;
	// else if (table->amount_philo == 1)
	// 	one_philo();	//TODO edgecase
	else
	{
		while (i < table->amount_philo)
		{
			philo = &table->philos[i];
			pthread_create(&philo->thread, NULL, &routine, philo);
			// printf("Thread %d created\n", i + 1);
			i++;
		}
		table->start = get_time_ms();
		i = 0;
		if (table->stop == true)
		{	
			while (i < table->amount_philo)
			{
				philo = &table->philos[i];
				pthread_join(philo->thread, NULL);
				// printf("Thread %d finished\n", i + 1);
				i++;
			}
		}
	}
}

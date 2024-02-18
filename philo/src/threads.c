/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:24:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/18 22:14:58 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg)
// thread: pointer to a pthread_t variable where thread ID will be stores after the thread is created
// attr: optional pointer to pthread_attr_t struct that allows you to specify various attributes for thread, such as stack size, schedulign policy etc. (USE NULL FOR DEFAULT ATTRIBUTES)
// start_routine: function pointer to the fucntion that will be executed by the new thread. takes void* and returns void*. entry point for the new thread
// arg: pointer to the arg that will be passed to start_Routine when thread is created.

void	*routine()
{
	return(NULL);
}

void	start_sim(t_table *table)
{
	t_philo *philo;
	int	i;
	
	i = 0;
	if (table->max_meals == 0)
		return ;
	// else if (table->amount_philo == 1)
	// 	one_philo();	//TODO edgecase
	else
	{
		while (i < table->amount_philo)
		{
			philo = &table->philos[i];
			pthread_create(&philo->thread, NULL, &routine, &table->philos[i]);
			printf("Thread %d created\n", i + 1);
			i++;
		}
		i = 0;
		while (i < table->amount_philo)
		{
			philo = &table->philos[i];
			pthread_join(philo->thread, NULL);
			printf("Thread %d finished\n", i + 1);
			i++;
		}
	}
}

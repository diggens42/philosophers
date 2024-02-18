/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:24:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/18 18:01:36 by fwahl            ###   ########.fr       */
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
	int	i;
	
	if (table->max_meals == 0)
		return ;
	// else if (table->amount_philo == 1)
	// 	one_philo();	//TODO edgecase
	else
	{
		i = 0;
		while (i < table->amount_philo)
		{
			pthread_create(&table->philos[i].thread_id, NULL, &routine, &table->philos[i]);
			i++;
		}
	}
}

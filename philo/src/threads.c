/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 20:24:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/17 20:59:15 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


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

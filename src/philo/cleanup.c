/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:07:57 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/14 21:27:24 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

void	cleanup(t_table *table)
{
	int	i;
	pthread_mutex_destroy(&table->info.sim);
	pthread_mutex_destroy(&table->info.eat);
	pthread_mutex_destroy(&table->info.print);
	i = 0;
	while (i < table->info.n_philos)
	{
		pthread_mutex_destroy(&table->philos[i].last_meal);
		i++;
	}
}

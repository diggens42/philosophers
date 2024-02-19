/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 17:25:20 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/19 17:38:13 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_saturation(t_table *table)
{
	t_philo	*philo;
	int		i;
	int		philos_full;

	i = 0;
	while (&table->philos[i] != NULL)
	{
		philo = &table->philos[i];
		if (philo->meals_eaten == table->max_meals)
			philos_full++;
		i++;
	}
	if (philos_full == table->amount_philo)
		table->stop = true;
	if (table->stop == true)
		exit_cleanup();
}

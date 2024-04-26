/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:00:34 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 23:01:30 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	synch_philo_starts(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->info.n_philos)
	{
		sem_post(table->info.start);
		i++;
	}
}

void	ft_error(char *error_msg)
{
	ft_sem_unlink();
	printf("Error: %s", error_msg);
	exit(EXIT_FAILURE);
}

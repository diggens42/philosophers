/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:30:28 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 22:41:54 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	simulation(t_table *table)
{
	if (table->info.n_philos == 1)
		one_philo(table);
	else
	{
	fork_philo_process(table);
	wait_philo_process(table);
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	ft_sem_unlink();
	check_input(argc, argv);
	init(&table, argv);
	simulation(&table);
	ft_sem_close(&table);
	ft_sem_unlink();
	return (0);
}

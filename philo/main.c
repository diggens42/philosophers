/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:15:35 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 19:20:42 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	simulation(t_table *table)
{
	start_philo_threads(table);
	start_monitor_thread(table);
	join_philo_threads(table);
	join_monitor_thread(table);
}

int	main(int argc, char **argv)
{
	t_table	table;

	check_input(argc, argv);
	init(&table, argv);
	simulation(&table);
	ft_mutex_destroy(&table);
	return (0);
}

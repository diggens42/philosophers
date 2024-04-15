/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:30:28 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:08:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		ft_error("too few / too many args");
		return (0);
	}
	cleanup_semaphores();
	check_argv(argv);
	init_bonus(&table, argv);
	simulation_bonus(&table);
	cleanup(&table);
	return (0);
}

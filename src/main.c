/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:15:35 by fwahl             #+#    #+#             */
/*   Updated: 2024/03/17 20:12:02 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		ft_error("too few / too many args");
		return (0);
	}
	check_argv(argv);
	init(&table, argv);
	simulation(&table);
	cleanup(&table);
	return (0);
}

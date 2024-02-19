/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:35:18 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/19 19:51:12 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_table	table;
	if (argc < 5 || argc > 6)
		ft_error("Too few / too many arguments");
	check_input(argv);
	init(&table, argv);
	start_sim(&table);
	return (EXIT_SUCCESS);
}
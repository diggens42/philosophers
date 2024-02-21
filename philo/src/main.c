/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:35:18 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/21 20:37:48 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (argc < 5 || argc > 6)
		ft_error("Too few / too many arguments\n");
	check_input(argv);
	init(table, argv);
	start_sim(table);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 20:49:43 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:08:26 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_argv(char **argv)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (argv[++i] != NULL)
	{
		len = 0;
		j = 0;
		while (ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '-')
			ft_error("No negative integers");
		if (!(ft_isdigit(argv[i][j])))
			ft_error("Wrong input");
		while (ft_isdigit(argv[i][j]))
		{
			j++;
			len++;
		}
		if (len > 10)
			ft_error("Input bigger than INT MAX");
	}
}

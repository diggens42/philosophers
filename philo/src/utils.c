/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:08:03 by fwahl             #+#    #+#             */
/*   Updated: 2024/02/15 20:23:01 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(char **str)
{
	printf("Error: %s", str);
	exit(EXIT_FAILURE);
}

long	ft_atol(const char *s)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (*s != '\0' && ((*s == ' ' || (*s >= '\t' && *s <= '\r'))))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
		if (*s == '-' || *s == '+')
			return (0);
	}
	while (ft_isdigit(*s))
	{
		result = result * 10 + *s - '0';
		s++;
	}
	return (sign * result);
}

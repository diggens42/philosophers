/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:05:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/15 19:56:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

bool	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

long	ft_atol(const char *s)
{
	long	result;
	long	sign;

	result = 0;
	sign = 1;
	while (*s != '\0' && (ft_isspace(*s)))
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

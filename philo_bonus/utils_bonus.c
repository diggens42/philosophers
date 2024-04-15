/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:05:44 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:26:29 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

suseconds_t	get_time_ms(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		ft_error("get time error");
	return ((time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000));
}

void	precise_usleep(long milliseconds)
{
	suseconds_t	time_start;
	suseconds_t	time_end;

	time_start = get_time_ms();
	time_end = time_start + milliseconds;
	while (get_time_ms() < time_end)
		usleep(100);
}

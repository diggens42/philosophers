/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:32:29 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 21:56:53 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_digit_counter(int n)
{
	int	digits;

	digits = 1;
	while (n >= 10)
	{
		digits++;
		n = n / 10;
	}
	return (digits);
}

static char	*ft_digit_output(int n, int digits, int sign)
{
	char	*str;
	int		i;

	i = 0;
	if (sign == -1)
		digits++;
	str = (char *)malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (sign == -1)
	{
		str[i] = '-';
		i++;
	}
	str[digits] = '\0';
	while (digits > i)
	{
		digits--;
		str[digits] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;
	int		digits;

	sign = 1;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		n = -n;
		sign = -1;
	}
	digits = ft_digit_counter(n);
	str = ft_digit_output(n, digits, sign);
	return (str);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;
	size_t	j;

	dest_len = 0;
	src_len = ft_strlen(src);
	while (dest[dest_len] != '\0' && dest_len < dest_size)
		dest_len++;
	if (dest_len >= dest_size)
		return (dest_size + src_len);
	i = dest_len;
	j = 0;
	while (i < dest_size - 1 && src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest_len + src_len);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(s1) + 1;
	copy = (char *)malloc(len);
	if (copy == NULL)
		return (NULL);
	ft_strlcpy(copy, s1, len);
	return (copy);
}

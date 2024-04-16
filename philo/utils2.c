/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 19:36:11 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 19:07:57 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *str)
{
	suseconds_t	time;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->stop_sim == true)
	{
		pthread_mutex_unlock(&philo->info->print);
		return ;
	}
	time = get_time_ms() - philo->time_start_routine;
	printf("%d Philo %d %s \n", time, philo->id, str);
	pthread_mutex_unlock(&philo->info->print);
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

void	ft_mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->info.n_philos)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		pthread_mutex_destroy(&table->philos[i].last_meal);
		i++;
	}
	pthread_mutex_destroy(&table->info.sim);
	pthread_mutex_destroy(&table->info.print);
}

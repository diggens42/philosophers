/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:11:01 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/26 23:54:44 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_unlink(void)
{
	int		i;
	char	last_meal_name[16];
	char	*temp;

	sem_unlink("print");
	sem_unlink("sim");
	sem_unlink("pid");
	sem_unlink("full");
	sem_unlink("forks");
	sem_unlink("start");
	i = 0;
	while (i <= 200)
	{
		ft_strlcpy(last_meal_name, "last_meal_", sizeof(last_meal_name));
		temp = ft_itoa(i);
		ft_strlcat(last_meal_name, temp, sizeof(last_meal_name));
		free(temp);
		sem_unlink(last_meal_name);
		i++;
	}
}

void	ft_sem_close(t_table *table)
{
	int		i;

	sem_close(table->info.print);
	sem_close(table->info.sim);
	sem_close(table->info.pid);
	sem_close(table->info.full);
	sem_close(table->info.forks);
	sem_close(table->info.start);
	i = 0;
	while (i < table->info.n_philos)
	{
		sem_close(table->philos[i].last_meal);
		i++;
	}
}

void	print_action(t_philo *philo, char *str)
{
	suseconds_t	time;

	sem_wait(philo->info->sim);
	if (philo->info->stop_sim == true)
	{
		sem_post(philo->info->sim);
		return ;
	}
	sem_post(philo->info->sim);
	time = get_time_ms() - philo->time_start_routine;
	sem_wait(philo->info->print);
	printf("%d Philo %d %s\n", time, philo->id, str);
	sem_post(philo->info->print);
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

suseconds_t	get_time_ms(void)
{
	struct timeval	time_value;

	if (gettimeofday(&time_value, NULL) == -1)
		ft_error("get time error");
	return ((time_value.tv_sec * 1000LL) + (time_value.tv_usec / 1000));
}

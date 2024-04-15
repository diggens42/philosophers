/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:28:25 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 01:08:07 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(char *error_msg)
{
	cleanup_semaphores();
	printf("Error: %s", error_msg);
	exit(EXIT_FAILURE);
}

void	cleanup_semaphores(void)
{
	sem_unlink("/print");
	sem_unlink("/sim");
	sem_unlink("/last_meal");
	sem_unlink("/forks");
}

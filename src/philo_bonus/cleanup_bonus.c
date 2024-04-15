/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:28:25 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/15 23:37:31 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo_bonus.h"

void	ft_error_semopen(char *error_msg)
{
	cleanup_semaphores();
	ft_error(error_msg);
}

void	cleanup_semaphores(void)
{
	sem_unlink("/print");
	sem_unlink("/sim");
	sem_unlink("/last_meal");
	sem_unlink("/forks");
}

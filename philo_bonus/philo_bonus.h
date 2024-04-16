/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwahl <fwahl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 21:20:48 by fwahl             #+#    #+#             */
/*   Updated: 2024/04/16 22:46:41 by fwahl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>

#define PHILOS_MAX 200

typedef struct s_info
{
	long			n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			n_meals_to_eat;
	bool			stop_sim;
	sem_t			*sim;
	sem_t			*print;
	sem_t			*forks;
}		t_info;

typedef struct s_philo
{
	int				id;
	int				n_meals_eaten;
	char			last_meal_name[16];
	sem_t			*last_meal;
	suseconds_t		time_last_meal;
	suseconds_t		time_start_routine;
	t_info			*info;
}		t_philo;

typedef struct s_table
{
	t_info			info;
	t_philo			philos[PHILOS_MAX];
}		t_table;

//error check
void		check_input(int argc, char **argv);
//init
void		init(t_table *table, char **argv);
//simulation
void		fork_philo_process(t_table *table);
void 		wait_philo_process(t_table *table);
void		start_monitor_thread(t_table *table);
void		take_forks(t_philo *philo);
//utils
bool		ft_isspace(char c);
bool		ft_isdigit(char c);
long		ft_atol(const char *s);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t dest_size);
char		*ft_strdup(const char *s1);
void		ft_error(char *error_msg);
void		ft_sem_unlink(void);
void		print_action(t_philo *philo, char *str);
void		precise_usleep(long milliseconds);
suseconds_t	get_time_ms(void);

#endif

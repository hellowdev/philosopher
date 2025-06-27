/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:16:09 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:21:54 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_args
{
	int				philos;
	int				time_died;
	int				time_eat;
	int				time_sleep;
	int				meals;
	int				count_meals;
	long			last_time_eat;
	bool			*check_die;
	pthread_mutex_t	*mute_dead;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_meals;
	pthread_mutex_t	*forks[2];
	int				index;
	long			start_time;
}	t_notshared;

typedef struct s_mute
{
	pthread_mutex_t	flag;
	pthread_mutex_t	write_init;
	pthread_mutex_t	meals;
	bool			checker;
}	t_shared;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				args_checker(char **arguments);
void			threads_init_forks(pthread_mutex_t *Mforks, t_notshared *data);
pthread_mutex_t	*inite_mfork(int philos);
int				sleep_func(t_notshared *data);
int				eating_func(t_notshared *data);
long			get_times(void);
void			convert_philos(t_notshared *data);
int				timer_sleep(int timer, t_notshared *data);
void			think_func(t_notshared *data);
void			*monitor_func(void *inp);
void			print_msg(t_notshared *data, char *msg);
int				mute_loops(t_notshared *data);
void			destroy_mutexes(int t, pthread_mutex_t *mforks);
void			threads_waiters(t_notshared *data, pthread_t *threads);
#endif
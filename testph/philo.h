#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <limits.h>
#include <stdbool.h>


typedef struct s_args
{
	int philos;
	int time_died;
	int time_eat;
	int time_sleep;
	int meals;
	pthread_mutex_t	*mute_dead;
	pthread_mutex_t	*mutex_print;
	pthread_mutex_t	*mutex_meals;
	// monitor
	long	last_time_eat;
	bool	*check_die;

	pthread_mutex_t *forks[2];
	int             index;
	long            start_time;
}   t_shared;


int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int	args_checker(char **arguments);

void	threads_init_forks(pthread_mutex_t *Mforks, t_shared *data);
pthread_mutex_t	*inite_Mfork(int philos);
int		sleep_func(t_shared *data);
int		eating_func(t_shared *data);
long	get_times();
void	convert_philos(t_shared *data);
int		timer_sleep(int timer, t_shared *data);
void	think_func(t_shared *data);
void	*monitor_func(void *inp);
void	print_lock(t_shared *data, char *msg);
#endif
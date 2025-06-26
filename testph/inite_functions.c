/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:09:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 18:24:15 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_notshared *data)
{
	if (data->philos == 1)
	{
		printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		timer_sleep(data->time_died, data);
	}
}

void	*thread_func(void *inp)
{
	t_notshared	*data;
	data = (t_notshared *)inp;
	
	one_philo(data);
	if (data->index % 2 == 1)
		timer_sleep(5, data);
	while (data->philos != 1 && mute_loops(data) != 1)
	{
		pthread_mutex_lock(data->forks[0]);
		print_lock(data, "has take left fork");
		pthread_mutex_lock(data->forks[1]);
		print_lock(data, "has take right fork");
		if (eating_func(data) == 1)
		{
			pthread_mutex_unlock(data->forks[0]);
			pthread_mutex_unlock(data->forks[1]);
			return (NULL);
		}
		pthread_mutex_unlock(data->forks[0]);
		pthread_mutex_unlock(data->forks[1]);
		if (sleep_func(data) == 1)
			return (NULL);
		think_func(data);
	}
	return (NULL);
}

void	threads_waiters(t_notshared *data, pthread_t *threads)
{
	int			i;
	long 		tmp;
	pthread_t	monitor;

	i = 0;
	tmp = get_times();
	while (i != data->philos)
	{
		data[i].start_time = tmp;
		data[i].last_time_eat = tmp;
		i++;
	}
	i = 0;
	pthread_create(&monitor, NULL, &monitor_func, data);
	while (i != data->philos)
	{
		pthread_create(&threads[i], NULL, &thread_func, &data[i]);
		i++;
	}
	i = 0;
	while (i != data->philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	
	pthread_join(monitor, NULL);
}

void	convert_philos(t_notshared *data)
{
	pthread_t       *threads; // declaration of thread
	pthread_mutex_t	*mforks;

	mforks = inite_Mfork(data->philos);
	threads = malloc(data->philos * sizeof(pthread_t));
	threads_init_forks(mforks, data);
	threads_waiters(data, threads);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:09:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 12:07:47 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_shared *data)
{
	if (data->philos == 1)
	{
		printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		timer_sleep(data->time_died, data);
	}
}

void	*thread_func(void *inp)
{
	t_shared	*data;
	data = (t_shared *)inp;
	
	one_philo(data);
	if (data->index % 2 == 1)
		timer_sleep(1, data);
	while (data->philos != 1 && *data->check_die != 1)
	{
		pthread_mutex_lock(data->forks[0]);
		print_lock(data, "has take left fork");
		// printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		pthread_mutex_lock(data->forks[1]);
		print_lock(data, "has take right fork");
		// printf("%ld %d has take right fork\n", get_times() - data->start_time, data->index);
		if (eating_func(data) == 1)
		{
			pthread_mutex_unlock(data->forks[0]);
			pthread_mutex_unlock(data->forks[1]);
			// printf("here %d\n", data->index);
			return (NULL);
		}
		pthread_mutex_unlock(data->forks[0]);
		pthread_mutex_unlock(data->forks[1]);
		if (sleep_func(data) == 1)
		{
			return (NULL);
		}
		think_func(data);
	}
	return (NULL);
}

void	threads_waiters(t_shared *data, pthread_t *threads)
{
	int	i;
	int j;
	int x;
	long tmp;
	pthread_t	monitor;

	j = 0;
	x = 0;
	i = 0;
	tmp = get_times();
	while (j != data->philos)
	{
		data[j].start_time = tmp;
		data[j].last_time_eat = tmp;
		j++;
	}
	pthread_create(&monitor, NULL, &monitor_func, data);
	while (i != data->philos)
	{
		pthread_create(&threads[i], NULL, &thread_func, &data[i]);
		i++;
	}
	while (x != data->philos)
	{
		pthread_join(threads[x], NULL);
		x++;
	}
	
	pthread_join(monitor, NULL);
}

void	convert_philos(t_shared *data)
{
	pthread_t       *threads; // declaration of thread
	pthread_mutex_t	*Mforks;

	Mforks = inite_Mfork(data->philos);
	threads = malloc(data->philos * sizeof(pthread_t));
	threads_init_forks(Mforks, data);
	threads_waiters(data, threads);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:09:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/22 15:12:01 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_func(void *inp)
{
	t_shared	*data;
	data = (t_shared *)inp;
	
	if (data->index % 2 == 1)
		ft_usleep(1);
	while (1)
	{
		pthread_mutex_lock(data->forks[0]);
		printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		pthread_mutex_lock(data->forks[1]);
		printf("%ld %d has take right fork\n", get_times() - data->start_time, data->index);
		eating_func(data);
		pthread_mutex_unlock(data->forks[0]);
		pthread_mutex_unlock(data->forks[1]);
		sleep_func(data);
		think_func(data);
	}
	return (NULL);
}
// void	monitor_thread(t_shared *data)
// {
// 	pthread_t	monitor;
// 	pthread_create(&monitor, NULL, &thread_func, &data);
// 	pthread_join(monitor, NULL);
// }
void	threads_waiters(t_shared *data, pthread_t *threads)
{
	int	i;
	int j;
	j = 0;
	i = 0;
	long tmp;
	tmp = get_times();
	while (j != data->philos)
	{
		data[j].start_time = tmp; 
		j++;
	}
	monitor_thread(data);
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

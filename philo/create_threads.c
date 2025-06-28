/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:09:59 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/28 13:36:03 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_notshared *data)
{
	if (data->philos == 1)
	{
		print_msg(data, "has taken a fork");
		timer_sleep(data->time_died, data);
		return ;
	}
}

void	*thread_func(void *inp)
{
	t_notshared	*data;

	data = (t_notshared *)inp;
	one_philo(data);
	if (data->index % 2 == 1)
		timer_sleep(3, data);
	while (mute_loops(data) != 1)
	{
		pthread_mutex_lock(data->forks[0]);
		print_msg(data, "has taken a fork");
		pthread_mutex_lock(data->forks[1]);
		print_msg(data, "has taken a fork");
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
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitor_func, data) != 0)
		return ((void)write(2, "Thread Not Created\n", 19));
	while (i != data->philos)
	{
		if (pthread_create(&threads[i], NULL, &thread_func, &data[i]) != 0)
			return ((void)write(2, "Thread Not Created\n", 19));
		i++;
	}
	i = 0;
	while (i != data->philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return ((void)write(2, "Thread Not Joined\n", 18));
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		return ((void)write(2, "Thread Not Joined\n", 18));
}

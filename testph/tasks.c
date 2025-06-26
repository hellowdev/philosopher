/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:07:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 12:15:59 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_times()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	timer_sleep(int timer, t_shared *data)
{
	long	start;
	start = get_times(); // 1000
	while (get_times() - start < timer) // get_time = 1200 - 1000 = 200  | timer = 200ms 
	{
		pthread_mutex_lock(data->mute_dead);
		if (*data->check_die == true)
			return (pthread_mutex_unlock(data->mute_dead), 1);
		pthread_mutex_unlock(data->mute_dead);
		usleep(100);
	}
	return (0);
}

int	eating_func(t_shared *data)
{
	
	pthread_mutex_lock(data->mute_dead);
	if (*data->check_die)
		return (pthread_mutex_unlock(data->mute_dead), 1);
	pthread_mutex_unlock(data->mute_dead);
	data->last_time_eat = get_times(); // timestamp of each meal
	print_lock(data, "is eating");
	return (timer_sleep(data->time_eat, data));
}

int	sleep_func(t_shared *data)
{
	pthread_mutex_lock(data->mute_dead);
	if (*data->check_die)
		return (pthread_mutex_unlock(data->mute_dead), 1);
	pthread_mutex_unlock(data->mute_dead);
	print_lock(data, "is sleeping");
	return (timer_sleep(data->time_sleep, data));
}

void	think_func(t_shared *data)
{
	pthread_mutex_lock(data->mute_dead);
	if (*data->check_die)
	{
		pthread_mutex_unlock(data->mute_dead);
		return ;
	}
	pthread_mutex_unlock(data->mute_dead);
	print_lock(data, "is thinking");
}

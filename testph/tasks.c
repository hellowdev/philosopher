/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:07:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 17:20:15 by ychedmi          ###   ########.fr       */
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
		if (mute_loops(data))
			return (1);
		usleep(200);
	}
	return (0);
}

int	eating_func(t_shared *data)
{
	
	if (mute_loops(data))
		return (1);
	pthread_mutex_lock(data->mutex_meals);
	data->last_time_eat = get_times();
	pthread_mutex_unlock(data->mutex_meals);
	print_lock(data, "is eating");
	return (timer_sleep(data->time_eat, data));
}

int	sleep_func(t_shared *data)
{
	if (mute_loops(data))
		return (1);
	print_lock(data, "is sleeping");
	return (timer_sleep(data->time_sleep, data));
}

void	think_func(t_shared *data)
{
	if (mute_loops(data))
		return ;
	print_lock(data, "is thinking");
}

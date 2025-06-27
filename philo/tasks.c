/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:07:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:29:48 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_times(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	timer_sleep(int timer, t_notshared *data)
{
	long	start;

	start = get_times();
	while (get_times() - start < timer)
	{
		if (mute_loops(data))
			return (1);
		usleep(500);
	}
	return (0);
}

int	eating_func(t_notshared *data)
{
	if (mute_loops(data))
		return (1);
	pthread_mutex_lock(data->mutex_meals);
	data->last_time_eat = get_times();
	data->count_meals++;
	pthread_mutex_unlock(data->mutex_meals);
	print_msg(data, "is eating");
	return (timer_sleep(data->time_eat, data));
}

int	sleep_func(t_notshared *data)
{
	if (mute_loops(data))
		return (1);
	print_msg(data, "is sleeping");
	return (timer_sleep(data->time_sleep, data));
}

void	think_func(t_notshared *data)
{
	if (mute_loops(data))
		return ;
	print_msg(data, "is thinking");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:07:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 10:51:12 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_times()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	timer_sleep(int timer, bool flag)
{
	long	start;

	start = get_times(); // 1000
	while (get_times() - start < timer) // get_time = 1200 - 1000 = 200  | timer = 200ms 
	{
		if (flag == true)
			return (1);
		usleep(500);
	}
	return (0);
}

int	eating_func(t_shared *data)
{
	if (data->flag_die)
		return (1);
	long eat = get_times();
	data->last_time_eat = eat; // timestamp of each meal
	eat = eat - data->start_time;
	printf("%ld %d is eating\n", eat, data->index);
	return (timer_sleep(data->time_eat, data->flag_die));
}

int	sleep_func(t_shared *data)
{
	if (data->flag_die)
		return (1);
	long sleep = get_times();
	sleep = sleep - data->start_time;
	printf("%ld %d is sleeping\n", sleep, data->index);
	return (timer_sleep(data->time_sleep, data->flag_die));
}

void	think_func(t_shared *data)
{
	if (data->flag_die)
		return ;
	printf("%ld %d is thinking\n", get_times() - data->start_time, data->index);
}

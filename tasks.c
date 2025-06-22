/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tasks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 10:07:50 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/22 13:25:47 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_times()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(int timer)
{
	long	start;

	start = get_times(); // 1000
	while (get_times() - start < timer) // get_time = 1200 - 1000 = 200  | timer = 200ms 
		usleep(500);
}

void	eating_func(t_shared *data)
{

	long eat = get_times();
	eat = eat - data->start_time;
	printf("%ld %d is eating\n", eat, data->index);
	ft_usleep(data->time_eat);
	
}

void	sleep_func(t_shared *data)
{
	long sleep = get_times();
	sleep = sleep - data->start_time;
	printf("%ld %d is sleeping\n", sleep, data->index);
	ft_usleep(data->time_sleep);
}

void	think_func(t_shared *data)
{
	long think = get_times();
	think = think - data->start_time;
	printf("%ld %d is thinking\n", think, data->index);
}

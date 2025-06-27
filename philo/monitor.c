/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:26:43 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dieflag(t_notshared *data)
{
	pthread_mutex_lock(data->mute_dead);
	*data->check_die = true;
	pthread_mutex_unlock(data->mute_dead);
}

int	eat_allmeals(t_notshared *data)
{
	int	i;

	i = 0;
	if (data->meals != -1)
	{
		while (i != data->philos)
		{
			pthread_mutex_lock(data->mutex_meals);
			if (data[i].count_meals < data[i].meals)
				return (pthread_mutex_unlock(data->mutex_meals), 0);
			pthread_mutex_unlock(data->mutex_meals);
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_died(t_notshared *data)
{
	pthread_mutex_lock(data->mutex_meals);
	if ((get_times() - data->last_time_eat) >= data->time_died)
	{
		set_dieflag(data);
		pthread_mutex_lock(data->mutex_print);
		printf("%ld %d is died\n", get_times() - data->start_time, data->index);
		pthread_mutex_unlock(data->mutex_print);
		return (pthread_mutex_unlock(data->mutex_meals), 1);
	}
	pthread_mutex_unlock(data->mutex_meals);
	if (eat_allmeals(data))
	{
		pthread_mutex_lock(data->mute_dead);
		*data->check_die = true;
		return (pthread_mutex_unlock(data->mute_dead), 1);
	}
	return (0);
}

void	*monitor_func(void *inp)
{
	t_notshared	*data;
	int			i;

	data = (t_notshared *)inp;
	while (1)
	{
		i = 0;
		while (i != data->philos)
		{
			if (check_died(&data[i]))
				return (NULL);
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 17:27:47 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mute_loops(t_shared *data)
{
	pthread_mutex_lock(data->mute_dead);
	if (*data->check_die == 1)
		return (pthread_mutex_unlock(data->mute_dead), 1);
	pthread_mutex_unlock(data->mute_dead);
	return (0);
}

void	print_lock(t_shared *data, char *msg)
{
	pthread_mutex_lock(data->mutex_print);
	if (mute_loops(data) != 1)
		printf("%ld %d %s\n", get_times() - data->start_time, data->index, msg);
	pthread_mutex_unlock(data->mutex_print);
}

void    set_dieflag(t_shared *data)
{
	int	i;

	i = 0;
	while (i != data->philos)
	{
		pthread_mutex_lock(data->mute_dead);
		*data[i].check_die = true;
		pthread_mutex_unlock(data->mute_dead);
		i++;
	}
}

int	check_died(t_shared *data)
{
	pthread_mutex_lock(data->mutex_meals);
	if ((get_times() - data->last_time_eat) >= data->time_died)
		return (pthread_mutex_unlock(data->mutex_meals), 1);
	pthread_mutex_unlock(data->mutex_meals);
	return (0);
}

void	*monitor_func(void *inp) 
{
	t_shared	*data;
	int i;

	data = (t_shared *)inp;
	while (1)
	{
		i = 0;
		while (i != data->philos)
		{	
			
			if (check_died(&data[i]))
			{
				set_dieflag(data);
				pthread_mutex_lock(data->mutex_print);
				printf("%ld %d is died\n", get_times() - data->start_time, data[i].index);
				pthread_mutex_unlock(data->mutex_print);
				return (NULL);
			}
			
			i++;
		}
	}
}

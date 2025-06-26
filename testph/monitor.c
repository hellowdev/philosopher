/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 12:14:06 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_lock(t_shared *data, char *msg)
{
	pthread_mutex_lock(data->mute_dead);
	if (!*data->check_die)
	{
		pthread_mutex_unlock(data->mute_dead);
		pthread_mutex_lock(data->mutex_print);
		printf("%ld %d %s\n", get_times() - data->start_time, data->index, msg);
		pthread_mutex_unlock(data->mutex_print);
		return ;
	}
	pthread_mutex_unlock(data->mute_dead);
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
			if ((get_times() - data[i].last_time_eat) >= data[i].time_died)
			{
				set_dieflag(data);
				printf("%ld %d is died\n", get_times() - data->start_time, data[i].index);
				return (NULL);
			}
			i++;
		}
	}
}

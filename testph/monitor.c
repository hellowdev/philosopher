/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/22 21:36:36 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_dieflag(t_shared *data)
{
	int	i;

	i = 0;
	while (i != data->philos)
	{
		data[i].flag_die = true;
		i++;
	}
}

void	*monitor_func(void *inp) 
{
	t_shared	*data;
	int i;

	data = (t_shared *)inp;
	i = 0;
	while (1)
	{
		while (i != data->philos)
		{
			data[i].flag_die = false;
			if ((get_times() - data[i].last_time_eat) >= data[i].time_died)
			{
				printf("%ld %d is died\n", get_times() - data->start_time, data->index);
				return (set_dieflag(data), NULL);
			}
			i++;
		}
	}
}

void	monitor_thread(t_shared *data)
{
	pthread_t	monitor;
	pthread_create(&monitor, NULL, &monitor_func, data);
	pthread_join(monitor, NULL);
}
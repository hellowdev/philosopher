/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 10:46:02 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_shared *data)
{
	if (data->philos == 1)
	{
		printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		timer_sleep(data->time_died, data);
	}
}

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
// 5 32 100 100
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
				printf("%ld %d is died\n", get_times() - data[i].start_time, data[i].index);
				return (NULL);
			}
			i++;
		}
	}
}


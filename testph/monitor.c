/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:21:36 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/23 13:39:59 by ychedmi          ###   ########.fr       */
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
				printf("%ld %d is died\n", get_times() - data->start_time, data->index);
				return (set_dieflag(data), NULL);
			}
			i++;
		}
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locked_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:52:05 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 14:52:22 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mute_loops(t_notshared *data)
{
	pthread_mutex_lock(data->mute_dead);
	if (*data->check_die == 1)
		return (pthread_mutex_unlock(data->mute_dead), 1);
	pthread_mutex_unlock(data->mute_dead);
	return (0);
}

void	print_msg(t_notshared *data, char *msg)
{
	pthread_mutex_lock(data->mutex_print);
	if (mute_loops(data) != 1)
		printf("%ld %d %s\n", get_times() - data->start_time, data->index, msg);
	pthread_mutex_unlock(data->mutex_print);
}
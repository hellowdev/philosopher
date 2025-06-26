/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:55:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 18:24:15 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*inite_Mfork(int philos)
{
	pthread_mutex_t	*mforks;
	int				i;

	i = 0;
	mforks = malloc(philos * sizeof(pthread_mutex_t));
	while (i != philos)
	{
		pthread_mutex_init(&mforks[i], NULL);
		i++;
	}
	return (mforks);
}

void	threads_init_forks(pthread_mutex_t *mforks, t_notshared *data)
{
	int	i;
	
	i = 0;
	
	while (i != data->philos)
	{
		data[i].forks[0] = &mforks[i];
		if (i + 1 == data->philos) // if last thread
			data[i].forks[1] = &mforks[0]; // change the last thread's fork wih first thread's fork
		else if (i + 1 != data->philos)
			data[i].forks[1] = &mforks[i + 1];
		data[i].index = i + 1;
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:55:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:22:57 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*inite_mfork(int philos)
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
		if (i + 1 == data->philos)
			data[i].forks[1] = &mforks[0];
		else if (i + 1 != data->philos)
			data[i].forks[1] = &mforks[i + 1];
		data[i].index = i + 1;
		i++;
	}
}

void	convert_philos(t_notshared *data)
{
	pthread_t		*threads;
	pthread_mutex_t	*mforks;
	int				i;

	i = 0;
	mforks = inite_mfork(data->philos);
	threads = malloc(data->philos * sizeof(pthread_t));
	threads_init_forks(mforks, data);
	threads_waiters(data, threads);
	free(threads);
	destroy_mutexes(data->philos, mforks);
	free(mforks);
}

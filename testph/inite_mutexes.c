/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inite_mutexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:55:10 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 11:54:17 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*inite_Mfork(int philos)
{
	pthread_mutex_t	*Mforks;
	int				i;

	i = 0;
	Mforks = malloc(philos * sizeof(pthread_mutex_t));
	while (i != philos)
	{
		pthread_mutex_init(&Mforks[i], NULL);
		i++;
	}
	return (Mforks);
}

void	threads_init_forks(pthread_mutex_t *Mforks, t_shared *data)
{
	int	i;
	pthread_mutex_t *flag;
	pthread_mutex_t *write;
	bool			*checker;

	flag = malloc(sizeof(pthread_mutex_t));
	write = malloc(sizeof(pthread_mutex_t));
	checker = malloc(sizeof(bool));
	i = 0;
	*checker = false;
	pthread_mutex_init(flag, NULL);
	pthread_mutex_init(write, NULL);
	while (i != data->philos)
	{
		data[i].mute_dead = flag;
		data[i].check_die = checker;
		data[i].mutex_print = write;
		data[i].forks[0] = &Mforks[i];
		if (i + 1 == data->philos) // if last thread
			data[i].forks[1] = &Mforks[0]; // change the last thread's fork wih first thread's fork
		else if (i + 1 != data->philos)
			data[i].forks[1] = &Mforks[i + 1];
		data[i].index = i + 1;
		i++;
	}
}

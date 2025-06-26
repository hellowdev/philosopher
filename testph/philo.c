/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:00:45 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/26 18:32:00 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_notshared	*true_args(char **args, t_shared *mute)
{
	t_notshared	*data;
	int			i;

	i = 0;
	
	data = malloc(ft_atoi(args[1]) * sizeof(t_notshared));
	while (i != ft_atoi(args[1]))
	{
		// WE SHARED HERE THESE MUTEX VARIABLE WITH A NON SHARED STRUCT,
		// CUZ WE NEED ALL THREADS KNOW THESE VARIABLES BY SHARED THEM WITH THIS WAY
		// AND LOCK AND UNLOCK THEM OR PLAY WITH THEM..
		data[i].mute_dead = &mute->flag;
		data[i].check_die = &mute->checker;
		data[i].mutex_print = &mute->write_init;
		data[i].mutex_meals = &mute->meals;
		// -------------------------------- //
		data[i].philos = ft_atoi(args[1]);
		data[i].time_died = ft_atoi(args[2]);
		data[i].time_eat = ft_atoi(args[3]);
		data[i].time_sleep = ft_atoi(args[4]);
		if (args[5])
			data[i].meals = ft_atoi(args[5]);
		i++;
	}
	return (data);
}

int main(int ac, char **av)
{
	t_notshared		*data;
	t_shared		mute;

	mute.checker = false;
	pthread_mutex_init(&mute.flag, NULL);
	pthread_mutex_init(&mute.meals, NULL);
	pthread_mutex_init(&mute.write_init, NULL);
	if (ac == 5 || ac == 6)
	{
		if (args_checker(av) != 0)
			return (1);
		data = true_args(av, &mute);
		convert_philos(data);
	}
	else
		return (write(2, "invalide argument\n", 18), 1);
}

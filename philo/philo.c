/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:00:45 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:15:52 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(int t, pthread_mutex_t *mforks)
{
	int	i;

	i = 0;
	while (i != t)
	{
		pthread_mutex_destroy(&mforks[i]);
		i++;
	}
}

t_notshared	*true_args(char **args, t_shared *mute)
{
	t_notshared	*data;
	int			i;

	i = 0;
	data = malloc(ft_atoi(args[1]) * sizeof(t_notshared));
	while (i != ft_atoi(args[1]))
	{
		data[i].mute_dead = &mute->flag;
		data[i].check_die = &mute->checker;
		data[i].mutex_print = &mute->write_init;
		data[i].mutex_meals = &mute->meals;
		data[i].count_meals = 0;
		data[i].start_time = get_times();
		data[i].last_time_eat = get_times();
		data[i].philos = ft_atoi(args[1]);
		data[i].time_died = ft_atoi(args[2]);
		data[i].time_eat = ft_atoi(args[3]);
		data[i].time_sleep = ft_atoi(args[4]);
		if (args[5])
			data[i].meals = ft_atoi(args[5]);
		else
			data[i].meals = -1;
		i++;
	}
	return (data);
}

int	main(int ac, char **av)
{
	t_notshared		*data;
	t_shared		mute;

	if (ac == 5 || ac == 6)
	{
		if (args_checker(av) != 0)
			return (1);
		mute.checker = false;
		pthread_mutex_init(&mute.flag, NULL);
		pthread_mutex_init(&mute.meals, NULL);
		pthread_mutex_init(&mute.write_init, NULL);
		data = true_args(av, &mute);
		convert_philos(data);
		free(data);
		pthread_mutex_destroy(&mute.flag);
		pthread_mutex_destroy(&mute.write_init);
		pthread_mutex_destroy(&mute.meals);
	}
	else
		return (write(2, "invalide argument\n", 18), 1);
}

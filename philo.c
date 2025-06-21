/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:00:45 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/21 18:56:00 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_times()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000000 + time.tv_usec) / 1000);
}

void	eating_func(t_shared *data)
{
	
	long eat = get_times();
	eat = eat - data->start_time;
	printf("%ld %d is eating\n", eat, data->index);
	usleep(data->time_eat * 1000);
	// pause();
	
}

void	*thread_func(void *inp)
{
	t_shared	*data;
	data = (t_shared *)inp;
	
	data->start_time = get_times();
	while (1)
	{
		if (data->index % 2 == 1)
		{
			printf("index > %d\n", data->index);
			usleep(data->time_eat * 1000);
		}
		pthread_mutex_lock(&data->forks[0]);
		printf("%ld %d has take left fork\n", get_times() - data->start_time, data->index);
		pthread_mutex_lock(&data->forks[1]);
		printf("%ld %d has take right fork\n", get_times() - data->start_time, data->index);
		eating_func(data);
		pthread_mutex_unlock(&data->forks[0]);
		pthread_mutex_unlock(&data->forks[1]);
	}
	return (NULL);
}


void	threads_waiters(t_shared *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i != data->philos)
	{
		pthread_create(&threads[i], NULL, &thread_func, &data[i]);
		i++;		
	}
	i = 0;
	while (i != data->philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	convert_philos(t_shared *data)
{
	pthread_t       *threads; // declaration of thread
	pthread_mutex_t	*Mforks;

	Mforks = inite_Mfork(data->philos);
	threads = malloc(data->philos * sizeof(pthread_t));
	threads_init_forks(Mforks, data);
	threads_waiters(data, threads);
	
}

t_shared	*true_args(char **args)
{
	t_shared	*data;
	int			i;

	i = 0;
	
	data = malloc(ft_atoi(args[1]) * sizeof(t_shared));
	while (i != ft_atoi(args[1]))
	{
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
	t_shared	*data;

	// data = NULL;
	if (ac == 5 || ac == 6)
	{
		if (args_checker(av) != 0)
			return (1);
		data = true_args(av);
		convert_philos(data);
	}
	else
		return (write(2, "invalide argument\n", 18), 1);
}

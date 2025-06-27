/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_parce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychedmi <ychedmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:12:18 by ychedmi           #+#    #+#             */
/*   Updated: 2025/06/27 20:24:42 by ychedmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_check(char *arg, int i)
{
	long	nb;

	nb = ft_atoi(arg);
	if ((nb <= 0 && i != 5) || (i == 5 && nb < 0))
	{
		write(2, "invalide numbers\n", 17);
		return (1);
	}
	return (0);
}

int	other_check(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
		return (write(2, "not valid numbers\n", 18), 1);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (write(2, "not valid numbers\n", 18), 1);
		i++;
	}
	return (0);
}

int	args_checker(char **arguments)
{
	int	i;

	i = 0;
	if (arguments[1])
		i = 1;
	while (arguments[i])
	{
		if (other_check(arguments[i]) != 0 || num_check(arguments[i], i) != 0)
			return (1);
		i++;
	}
	return (0);
}

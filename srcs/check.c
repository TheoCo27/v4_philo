/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:21:59 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:42:48 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock_alive);
	if (philo->data->all_alive == 0)
		return (pthread_mutex_unlock(&philo->data->lock_alive), 0);
	pthread_mutex_unlock(&philo->data->lock_alive);
	return (1);
}

int	check_overflow(const char *str)
{
	long	i;
	long	result;

	result = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result > INT_MAX)
			return (0);
	}
	return (1);
}

int	check_argv(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_str_isdigit(av[i]) == 0 || check_overflow(av[i]) == 0
			|| ft_atoi(av[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
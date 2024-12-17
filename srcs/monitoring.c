/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 21:33:28 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:53:20 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_meal(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_meals_wanted == -1)
		return (0);
	else
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&data->philo[i].lock_nb_meal);
			if (data->nb_meals_wanted > data->philo[i].nb_meal)
				return (pthread_mutex_unlock(&data->philo[i].lock_nb_meal), 0);
			pthread_mutex_unlock(&data->philo[i].lock_nb_meal);
			i++;
		}
	}
	return (1);
}

void	*monitor(void *args)
{
	t_data	*data;
	int		i;
	data = (t_data *)args;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&data->philo[i].lock_last_meal);
		if (get_time_in_ms() - data->philo[i].last_meal > data->time_to_die)
		{
			stop_philo(data, i, 0);
			break ;
		}
		pthread_mutex_unlock(&data->philo[i].lock_last_meal);
		if (check_nb_meal(data) == 1)
		{
			stop_philo(data, i, 1);
			break ;
		}
		i++;
		if (i >= data->nb_philo)
			i = 0;
		usleep(1);
	}
	return (NULL);
}

void	stop_philo(t_data *data, int i, int bool)
{
	pthread_mutex_lock(&data->speak);
	pthread_mutex_lock(&data->lock_alive);
	data->all_alive = 0;
	pthread_mutex_unlock(&data->lock_alive);
	if (bool == 0)
		printf("%ld %d died\n", get_time_in_ms() - data->time_start, i + 1);
	else
		printf("%ld all philo ate\n", get_time_in_ms() - data->time_start);
	pthread_mutex_unlock(&data->speak);
	if (bool == 0)
		pthread_mutex_unlock(&data->philo[i].lock_last_meal);
}
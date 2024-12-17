/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:15 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:55:59 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i].lock_nb_meal);
		pthread_mutex_destroy(&data->philo[i].right_fork);
		pthread_mutex_destroy(&data->philo[i++].lock_last_meal);
	}
	pthread_mutex_destroy(&data->start);
	pthread_mutex_destroy(&data->lock_alive);
	pthread_mutex_destroy(&data->speak);
}

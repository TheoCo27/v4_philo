/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:22:25 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:43:56 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*lonely_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("%d %d has taken a fork\n", 0, philo->id);
	while (get_time_in_ms() - philo->last_meal < philo->data->time_to_die)
	{
	}
	printf("%ld %d died\n", get_time_in_ms() - philo->time_start, philo->id);
	return (NULL);
}

int	launch_philo_alone(t_data *data)
{
	set_time_start(data);
	pthread_create(&data->philo[0].thread, NULL, lonely_philo,
		&data->philo[0]);
	pthread_join(data->philo[0].thread, NULL);
	return (0);
}

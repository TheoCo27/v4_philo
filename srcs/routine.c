/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:35:18 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:48:50 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	// pthread_mutex_lock(&philo->data->start);
	// pthread_mutex_unlock(&philo->data->start);
	thinking(philo, 0);
	start_waiting(philo);
	while (check_all_alive(philo))
	{
		if (philo->id % 2 == 0)
			take_fork_even(philo);
		else
			take_fork_odd(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo, 1);
	}
	return (NULL);
}

void	start_waiting(t_philo *philo)
{
	if (philo->nb_philo % 2)
	{
		if (philo->id != 1 && philo->id % 2)
			ft_usleep(philo->time_to_eat / 2);
		else if (philo->id % 2 == 0)
			ft_usleep((philo->time_to_eat / 2) + 1);
	}
	else
	{
		if (philo->id % 2 == 0)
			ft_usleep(philo->time_to_eat / 2);
	}
}
void	ft_usleep(int nb)
{
	long	time;

	time = get_time_in_ms();
	while (get_time_in_ms() - time < nb)
	{
		usleep(1);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:07 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:46:18 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d is eating\n", get_time_in_ms() - philo->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(&philo->lock_last_meal);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->lock_last_meal);
	if (check_all_alive(philo))
		ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_lock(&philo->lock_nb_meal);
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->lock_nb_meal);
}

void	take_fork_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
}

void	take_fork_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	pthread_mutex_lock(&philo->right_fork);
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d has taken a fork\n", get_time_in_ms()
			- philo->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->speak);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
		printf("%ld %d is sleeping\n", get_time_in_ms() - philo->time_start,
			philo->id);
	pthread_mutex_unlock(&philo->data->speak);
	if (check_all_alive(philo))
		ft_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo, int bool)
{
	pthread_mutex_lock(&philo->data->speak);
	if (check_all_alive(philo))
	{
		printf("%ld %d is thinking\n", get_time_in_ms() - philo->time_start,
			philo->id);
	}
	pthread_mutex_unlock(&philo->data->speak);
	if (bool && philo->nb_philo % 2 && philo->time_to_eat >= 2
		* philo->time_to_sleep)
		ft_usleep(philo->time_to_eat);
	else if (bool && philo->nb_philo % 2)
		ft_usleep(philo->time_to_eat / 3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:23:22 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:36:54 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->nb_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_start = get_time_in_ms();
	data->all_alive = 1;
	if (ac == 6)
		data->nb_meals_wanted = ft_atoi(av[5]);
	else
		data->nb_meals_wanted = -1;
	while (i < data->nb_philo && i < 200)
	{
		data->philo[i].nb_philo = data->nb_philo;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].bool_alive = 1;
		data->philo[i].nb_meal = 0;
		data->philo[i].last_meal = data->time_start;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i++].time_to_eat = data->time_to_eat;
	}
}

void	creat_mutex(t_data *data, int *i)
{
	pthread_mutex_init(&data->philo[*i].lock_nb_meal, NULL);
	pthread_mutex_init(&data->philo[*i].right_fork, NULL);
	pthread_mutex_init(&data->philo[*i].lock_last_meal, NULL);
	*i += 1;
	if (*i < data->nb_philo)
		data->philo[*i].left_fork = &data->philo[*i - 1].right_fork;
}

void	init_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
		creat_mutex(data, &i);
	data->philo[0].left_fork = &data->philo[i - 1].right_fork;
	pthread_mutex_init(&data->speak, NULL);
	pthread_mutex_init(&data->lock_alive, NULL);
	pthread_mutex_init(&data->start, NULL);
	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, routine,
			&data->philo[i]);
		i++;
	}
	set_time_start(data);
	pthread_mutex_unlock(&data->start);
	monitor(data);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(data->philo[i++].thread, NULL);
	return (ft_destroy_mutex(data));
}

void	set_time_start(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = get_time_in_ms();
	while (i < data->nb_philo)
	{
		data->philo[i].last_meal = data->time_start;
		data->philo[i].time_start = data->time_start;
		i++;
	}
}

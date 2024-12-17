/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:22:44 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:44:16 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (printf("nb_philo time_to_die time_to_eat time_to_sleep\n"));
	if (check_argv(ac, av) == 0)
		return (printf("error args\n"));
	init_data(ac, av, &data);
	if (data.nb_philo > 200)
		return (printf("max philo = 200\n"), 0);
	if (data.nb_philo == 1)
		return (launch_philo_alone(&data));
	else
		return (init_simulation(&data), 0);
}

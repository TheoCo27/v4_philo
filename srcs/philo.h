/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theog <theog@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:22:58 by theog             #+#    #+#             */
/*   Updated: 2024/12/17 21:46:18 by theog            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				bool_alive;
	long			last_meal;
	int				nb_meal;
	int				time_to_eat;
	int				nb_philo;
	int				time_to_sleep;
	long			time_start;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	lock_last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	lock_nb_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	start;
	pthread_mutex_t	speak;
	pthread_mutex_t	lock_alive;
	long			time_start;
	int				all_alive;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_wanted;
	t_philo			philo[200];
}					t_data;

long				get_time_in_ms(void);
int					ft_atoi(const char *str);
int					ft_str_isdigit(char *str);
int					check_overflow(const char *str);
int					check_argv(int ac, char **av);
void				init_data(int ac, char **av, t_data *data);
int					check_argv(int ac, char **av);
int					launch_philo_alone(t_data *data);
void				*monitor(void *args);
void				init_simulation(t_data *data);
void				take_fork_even(t_philo *philo);
void				take_fork_odd(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo, int bool);
void				eating(t_philo *philo);
void				ft_destroy_mutex(t_data *data);
void				start_waiting(t_philo *philo);
void				ft_usleep(int nb);
int					check_nb_meal(t_data *data);
void				stop_philo(t_data *data, int i, int bool);
int					check_all_alive(t_philo *philo);
void				set_time_start(t_data *data);
void				*routine(void *args);
#endif
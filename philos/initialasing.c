/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:34:42 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/07 00:00:42 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].t_die = data->t_die;
		philos[i].t_eat = data->t_eat;
		philos[i].t_sleap = data->t_sleap;
		philos[i].nb_philo = data->n_philo;
		philos[i].last_meal = 0;
		philos[i].eated = 0;
		philos[i].meals_eaten = 0;
		philos[i].is_dead = 0;
		philos[i].own_fork = &mutex[i];
		philos[i].left_fork = &mutex[(i + 1) % data->n_philo];
	}
}

void	check_failed(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	if ((philos != NULL && data != NULL && mutex != NULL))
		return ;
	if (philos != NULL)
		free(philos);
	if (data != NULL)
		free(data);
	if (mutex != NULL)
		free(mutex);
	exit (2);
}

void	init(t_philo *philos, t_data *data, pthread_mutex_t *mutex)
{
	int	i;
	int	count;

	check_failed(philos, data, mutex);
	i = -1;
	count = 0;
	while (++i < data->n_philo)
		count += pthread_mutex_init(&mutex[i], NULL);
	count += pthread_mutex_init(&data->lock_time_start, NULL);
	count += pthread_mutex_init(&data->lock_print, NULL);
	count += pthread_mutex_init(&data->lock_last_meal, NULL);
	count += pthread_mutex_init(&data->lock_die, NULL);
	if (count != 0)
	{
		free(philos);
		free(data);
		free(mutex);
		exit (2);
	}
	init_philos(philos, data, mutex);
}

int	fill_data(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->die = 0;
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleap = ft_atoi(av[4]);
	if (av[5])
		data->meals = ft_atoi(av[5]);
	else
		data->meals = -1;
	if (data->n_philo <= 0 || (av[5] && data->meals <= 0))
		return (1);
	return (0);
}

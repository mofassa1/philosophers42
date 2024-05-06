/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:16:38 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/03 22:36:39 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philos_creation(t_philo *philos, t_data *data)
{
	int			i;

	i = 0;
	data->t = get_time();
	while (i < data->n_philo)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	monitor(philos, data);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	printf("%lu %d died\n", \
			data->death_time - data->t, philos[data->die_index].id);
}

int	main(int ac, char **av)
{
	pthread_mutex_t	*mutex;
	t_philo			*philos;
	t_data			*data;

	if ((ac != 6 && ac != 5) || check_arg(av))
		return (errors(INVALI_ARGS, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (fill_data(data, av))
		return (errors(INVALI_VAL, data));
	philos = ((t_philo *)malloc((data->n_philo) * sizeof(t_philo)));
	mutex = (pthread_mutex_t *)malloc(data->n_philo * sizeof(pthread_mutex_t));
	init(philos, data, mutex);
	philos_creation(philos, data);
	free(data);
	free(mutex);
	free(philos);
	return (SUCSESS);
}

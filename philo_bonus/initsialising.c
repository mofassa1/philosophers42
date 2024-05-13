/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initsialising.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 22:05:33 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/11 16:19:04 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_data(t_data *data, char **av)
{
	if (data == NULL)
	{
		printf("malloc failed\n");
		exit (3);
	}
	data->meals_eated = 0;
	data->t = get_time();
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
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		free (data);
		printf("init mutex failed\n");
		exit (4);
	}
	return (0);
}

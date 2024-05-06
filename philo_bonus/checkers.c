/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:30:20 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/07 00:07:20 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	finish_meals(t_data *data)
{
	if (data->meals < 0 || data->meals_eated < data->meals)
		return (0);
	return (1);
}

void	*is_dead(void *data1)
{
	t_data	*data;

	data = (t_data *)data1;
	while (1)
	{
		sem_wait(data->death);
		if (get_time() - data->last_meal > data->t_die \
			|| finish_meals(data))
		{
			sem_wait(data->lock_print);
			printf("%lu %d died\n", get_time() - data->t, data->id);
			exit (4);
		}
		sem_post(data->death);
	}
	return (NULL);
}

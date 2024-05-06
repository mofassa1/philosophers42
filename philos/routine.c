/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:37:23 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/03 20:00:55 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	if (print(philo, EATING))
	{
		UNLOCK(philo->left_fork);
		UNLOCK(philo->own_fork);
		return (1);
	}
	LOCK(&philo->data->lock_last_meal);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	UNLOCK(&philo->data->lock_last_meal);
	ft_usleep(philo->t_eat);
	UNLOCK(philo->own_fork);
	UNLOCK(philo->left_fork);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (print(philo, THINKING))
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	LOCK(&philo->data->lock_die);
	if (philo->data->die)
	{
		UNLOCK(&philo->data->lock_die);
		return (1);
	}
	UNLOCK(&philo->data->lock_die);
	LOCK(&philo->data->lock_print);
	printf("%lu %d is sleeping\n", get_time() - philo->data->t, philo->id);
	UNLOCK(&philo->data->lock_print);
	ft_usleep(philo->t_sleap);
	return (0);
}

void	*routine(void *tphilo)
{
	t_philo	*philo;

	philo = (t_philo *)tphilo;
	LOCK(&philo->data->lock_last_meal);
	philo->last_meal = philo->data->t;
	UNLOCK(&philo->data->lock_last_meal);
	while (1)
	{
		if (is_dead(philo))
			break ;
		if (first_fork(philo))
			break ;
		if (second_fork(philo))
			break ;
		if (eating(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

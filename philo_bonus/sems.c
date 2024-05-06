/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sems.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:28:51 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/06 23:45:28 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	close_sem(t_data *data, pid_t *pid)
{
	int	i;

	i = 0;
	sem_close(data->lock_print);
	sem_close(data->death);
	sem_close(data->forks);
	while (i < data->n_philo)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
}

void	init_sems2(t_data *data, pid_t *pid)
{
	sem_unlink("/forks_sem");
	data->forks = sem_open("/forks_sem", O_CREAT | O_EXCL, 0644, data->n_philo);
	if (data->forks == SEM_FAILED)
	{
		free(pid);
		sem_close(data->lock_print);
		sem_close(data->death);
		exit (8);
	}
}

void	init_sems(t_data *data, pid_t *pid)
{
	if (pid == NULL)
		exit (5);
	sem_unlink("/print_sem");
	data->lock_print = sem_open("/print_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->lock_print == SEM_FAILED)
	{
		free(pid);
		free(data);
		exit (6);
	}
	sem_unlink("/death_sem");
	data->death = sem_open("/death_sem", O_CREAT | O_EXCL, 0644, 1);
	if (data->death == SEM_FAILED)
	{
		free(pid);
		free(data);
		sem_close(data->lock_print);
		exit (7);
	}
	init_sems2(data, pid);
}

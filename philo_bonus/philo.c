/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afadouac <afadouac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 21:08:04 by afadouac          #+#    #+#             */
/*   Updated: 2024/05/06 23:45:41 by afadouac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int				i;
	pid_t			*pid;
	t_data			*data;

	i = 0;
	if ((ac != 6 && ac != 5) || check_arg(av))
		return (errors(INVALI_ARGS, NULL));
	data = (t_data *)malloc(sizeof(t_data));
	if (fill_data(data, av))
		return (errors(INVALI_VAL, data));
	pid = (pid_t *)malloc(sizeof(pid_t) * data->n_philo);
	init_sems(data, pid);
	while (i < data->n_philo)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			routine(data, i + 1);
		if (pid[i] < 0)
			return (free(pid), free(data), FORK_FAILED);
		i++;
	}
	waitpid(-1, NULL, 0);
	close_sem(data, pid);
	free(data);
	free(pid);
}

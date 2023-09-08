/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:41:19 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 22:22:05 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	create_philos_1(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	if (data->numofphilos % 2 != 0)
	{
		i = 0;
		if (pthread_create(&philos[i].tid, NULL, \
			t_philosopher, &philos[i]) != 0)
			printf("\nThread can't be created");
	}
	while (++i < data->numofphilos)
	{
		if (i % 2 == 0)
			if (pthread_create(&philos[i].tid, NULL, \
			t_philosopher, &philos[i]) != 0)
				printf("\nThread can't be created");
	}
}

void	create_philos_2(t_philo *philos, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->numofphilos)
	{
		if (i % 2 != 0)
			if (pthread_create(&philos[i].tid, NULL, \
			t_philosopher, &philos[i]) != 0)
				printf("\nThread can't be created");
	}
	i = -1;
	while (++i < data->numofphilos)
	{
		pthread_join(philos[i].tid, NULL);
	}
}

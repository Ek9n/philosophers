/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:26 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 22:28:37 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	static t_data	data;
	static t_philo	*philos;
	int				i;

	if (argc == 5 || argc == 6)
	{
		init_data(&data, argc, argv);
		philos = ft_calloc(data.numofphilos, sizeof(t_philo));
		i = -1;
		while (++i < data.numofphilos)
			init_philos(philos, &data, argc, i);
		create_philos_1(philos, &data);
		create_philos_2(philos, &data);
	}
	else
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	pthread_mutex_destroy(&data.deadlock);
	pthread_mutex_destroy(&data.printlock);
	free(philos);
	return (0);
}

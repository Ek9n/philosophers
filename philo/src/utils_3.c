/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:41:19 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 22:24:48 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	f_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->printlock);
	printmsg(philo, sleeping);
	pthread_mutex_unlock(&philo->data->printlock);
	usleep(philo->timetosleep * 1000);
}

void	*t_philosopher(void *param)
{
	size_t	time;
	t_philo	*philo;

	philo = (t_philo *)param;
	time = get_time(philo->start_time);
	if (philo->numofphilos == 1)
	{
		usleep(philo->timetodie * 1000);
		printf("%d %d died\n", get_time(philo->start_time), philo->n);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printmsg(philo, thinking);
		pthread_mutex_unlock(&philo->data->printlock);
		f_forking(philo);
		philo->life = philo->timetodie;
		f_eating(philo);
		f_sleeping(philo);
	}
	return (NULL);
}

void	init_data(t_data *data, int argc, char **argv)
{
	data->start_time = current_time();
	data->numofphilos = ft_atoi(argv[1]);
	data->timetodie = ft_atoi(argv[2]);
	data->timetoeat = ft_atoi(argv[3]);
	data->timetosleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->maxmeals = ft_atoi(argv[5]) * data->numofphilos;
	pthread_mutex_init(&data->printlock, NULL);
	pthread_mutex_init(&data->deadlock, NULL);
}

void	init_philos(t_philo *philos, t_data *data, int argc, int i)
{
	philos[i].start_time = data->start_time;
	philos[i].numofphilos = data->numofphilos;
	if (argc == 6)
		philos[i].maxmeals = data->maxmeals / data->numofphilos;
	philos[i].timetodie = data->timetodie;
	philos[i].life = data->timetodie;
	philos[i].timetoeat = data->timetoeat;
	philos[i].timetosleep = data->timetosleep;
	philos[i].data = data;
	philos[i].n = i + 1;
	philos[i].right_fork = &philos[(i + 1) % data->numofphilos].fork;
	pthread_mutex_init(&philos[i].fork, NULL);
}

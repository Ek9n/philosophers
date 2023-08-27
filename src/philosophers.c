/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:26 by hstein            #+#    #+#             */
/*   Updated: 2023/08/28 00:25:42 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// memset, printf, malloc, free, write,
// usleep, gettimeofday, pthread_create,
// pthread_detach, pthread_join, pthread_mutex_init,
// pthread_mutex_destroy, pthread_mutex_lock,
// pthread_mutex_unlock
//NO LIBFT

// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died
// Replace timestamp_in_ms with the current timestamp in milliseconds
// and X with the philosopher number.
// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]

void	*t_philosopher(void *param)
{
	t_philo	*philo = (t_philo *)param;
	pthread_mutex_t *tmp_rightfork;
		// printf("HALLO\n");

	while (1)
	{
		if (philo->data->numofphilos == 1)
		{
			usleep(philo->data->timetodie * 1000);
			printf("%d %d died\n", get_time(philo->data), philo->n);
			return (NULL);
		}
		if (philo->n == philo->data->numofphilos)
		{
			tmp_rightfork = &(philo - philo->data->numofphilos)->fork;
			pthread_mutex_lock(&philo->fork);
			pthread_mutex_lock(tmp_rightfork);
		}
		else
		{
			tmp_rightfork = &(philo + 1)->fork;
			pthread_mutex_lock(&philo->fork);
			pthread_mutex_lock(tmp_rightfork);
		}
		usleep(philo->data->timetoeat * 1000);
		printf("%d %d is eating\n", get_time(philo->data), philo->n);
		// printf("PhiloN%d\n", philo->n);
		// pthread_mutex_lock(&(philo + 1)->fork);
		// sleep (doing nothing)
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(tmp_rightfork);

	}
	// eat
	// think (wait/try to eat)

	// pthread_mutex_lock(&philo->data->lock);
	// printf("numofphilo=%d\n", data->numofphilo);
	// for(int i = 0; i < 1; i++)
	// {
	// 	printf("philosopher%d\n", philo->n);
	// 	printf("id=%lu\n", philo->tid);
	// }
	// pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	static t_data	data;
	static t_philo	*philos;

	int	i = -1;

	if (argc == 4 || argc == 5)
	{
		data.start_time = current_time();
		data.numofphilos = ft_atoi(argv[1]);
		data.timetodie = ft_atoi(argv[2]);
		data.timetoeat = ft_atoi(argv[3]);
		data.timetosleep = ft_atoi(argv[4]);
		// printf("numofphilos=%d\n", data.numofphilos);
		// printf("numofphilos=%d\n", data.timetodie);
		// printf("numofphilos=%d\n", data.timetoeat);
		// printf("numofphilos=%d\n\n", data.timetosleep);

		philos = malloc(data.numofphilos * sizeof(t_philo));
		while (++i < data.numofphilos)
		{
			philos[i].data = &data;
			philos[i].n = i + 1;
		}
        pthread_mutex_init(&data.lock, NULL);
		i = -1;
		while(++i < data.numofphilos)
		{
        	if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
           		printf("\nThread can't be created");
		}
		i = -1;
		while (++i < data.numofphilos)
    		pthread_join(philos[i].tid, NULL);
	}
	else
	{
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	}

    // pthread_mutex_destroy(&data.lock);
	free(philos);

	return (0);
}

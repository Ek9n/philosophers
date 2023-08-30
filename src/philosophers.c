/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:26 by hstein            #+#    #+#             */
/*   Updated: 2023/08/30 18:30:40 by hstein           ###   ########.fr       */
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
	int			life;

	life = philo->timetodie;
	int next_philo_index = ((philo->n + 1) % philo->numofphilos) - 1;
	tmp_rightfork = &(philo[next_philo_index].fork);

	if (philo->numofphilos == 1)
	{
		usleep(philo->timetodie * 1000);
		printf("%d %d died\n", get_time(philo->data), philo->n);
		return (NULL);
	}

	while (1) // flag fuer death
	{
	// think
		
	// eat

	// sleep
		usleep(philo->timetosleep * 1000);
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is sleeping\n", get_time(philo->data), philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
	}



	while (1)
	{
		if (life <= 0)
		{
				pthread_mutex_lock(&philo->data->printlock);
			printf("%d %d died\n", get_time(philo->data), philo->n);
				pthread_mutex_unlock(&philo->data->printlock);
			return (NULL);
		}
			pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is thinking\n", get_time(philo->data), philo->n);
			pthread_mutex_unlock(&philo->data->printlock);

		pthread_mutex_lock(&philo->fork);
			pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d has taken a fork\n", get_time(philo->data), philo->n);
			pthread_mutex_unlock(&philo->data->printlock);
		pthread_mutex_lock(tmp_rightfork);
			pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d has taken a fork\n", get_time(philo->data), philo->n);
			pthread_mutex_unlock(&philo->data->printlock);

	life = philo->timetodie;
	life -= philo->data->timetoeat;
	// printf("Philo:%d, life_1=%d\n", philo->n, life);
		printf("%d %d is eating\n", get_time(philo->data), philo->n);
		usleep(philo->timetoeat * 1000);
			pthread_mutex_lock(&philo->data->printlock);
			pthread_mutex_unlock(&philo->data->printlock);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(tmp_rightfork);
		if (life <= 0)
		{
				pthread_mutex_lock(&philo->data->printlock);
			printf("%d %d died\n", get_time(philo->data), philo->n);
				pthread_mutex_unlock(&philo->data->printlock);
			return (NULL);
		}

			pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is sleeping\n", get_time(philo->data), philo->n);
			pthread_mutex_unlock(&philo->data->printlock);
		usleep(philo->timetosleep * 1000);
	life -= philo->timetosleep;
	// printf("Philo:%d, life_2=%d\n", philo->n, life);
		if (life <= 0)
		{
				pthread_mutex_lock(&philo->data->printlock);
			printf("%d %d died\n", get_time(philo->data), philo->n);
				pthread_mutex_unlock(&philo->data->printlock);
			return (NULL);
		}
		// printf("PhiloN%d\n", philo->n);
		// pthread_mutex_lock(&(philo + 1)->fork);
		// sleep (doing nothing)

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
	int sleeptime = 1000;

	if (argc == 4 || argc == 5)
	{
		data.start_time = current_time();
		data.numofphilos = ft_atoi(argv[1]);
		data.timetodie = ft_atoi(argv[2]);
		data.timetoeat = ft_atoi(argv[3]);
		data.timetosleep = ft_atoi(argv[4]);
		pthread_mutex_init(&data.printlock, NULL);
		philos = malloc(data.numofphilos * sizeof(t_philo));
		while (++i < data.numofphilos)
		{
			philos[i].start_time = data.start_time;
			philos[i].numofphilos = data.numofphilos;
			philos[i].timetodie = data.timetodie;
			philos[i].timetoeat = data.timetoeat;
			philos[i].timetosleep = data.timetosleep;
			philos[i].data = &data;
			philos[i].n = i + 1;
			pthread_mutex_init(&philos[i].fork, NULL);
		}
		i = -1;
		if (data.numofphilos % 2 == 0)
		{
			i = -1;
			while (++i < data.numofphilos)
			{
				if (i % 2 != 0)
				{
					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
						printf("\nThread can't be created");
				}
			}	
			usleep(sleeptime);
			i = -1;	
			while (++i < data.numofphilos)
			{
				if (i % 2 == 0)
				{
					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
						printf("\nThread can't be created");
				}
			}
		}
		else
		{
			if (pthread_create(&philos[0].tid, NULL, t_philosopher, &philos[0]) != 0)
				printf("\nThread can't be created");
			i = 0;
			usleep(sleeptime);
			while (++i < data.numofphilos)
			{
				if (i % 2 != 0)
				{
					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
						printf("\nThread can't be created");
				}
			}	
			usleep(sleeptime);
			i = 0;	
			while (++i < data.numofphilos)
			{
				if (i % 2 == 0)
				{
					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
						printf("\nThread can't be created");
				}
			}
		}
		i = -1;
		while (++i < data.numofphilos)
    		pthread_join(philos[i].tid, NULL);
	}
	else
	{
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	}

    // pthread_mutex_init(&data.lock, NULL);
    // pthread_mutex_destroy(&data.lock);
	free(philos);

	return (0);
}

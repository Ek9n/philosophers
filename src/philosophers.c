/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:26 by hstein            #+#    #+#             */
/*   Updated: 2023/09/05 00:19:06 by hstein           ###   ########.fr       */
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


void	printmsg(t_philo *philo, enum week opt)
{
	static int	prevtime;
	int			time = get_time(philo->start_time);
	philo->life -= time - prevtime;
	
	pthread_mutex_lock(&philo->data->printlock);
	printf("  philo:%d, time:%d, life:%d\n", philo->n, time, philo->life);
	pthread_mutex_unlock(&philo->data->printlock);


	// pthread_mutex_lock(&philo->data->deadlock);
	// if (philo->data->deadflag)
	// {
	// 	// opt = 0;
	// }
	// pthread_mutex_unlock(&philo->data->deadlock);

	if (philo->life <= 0)
	{
		opt = 0;
	}
	// pthread_mutex_lock(&philo->data->printlock);
	// get_time(philo->data)//
	// pthread_mutex_unlock(&philo->data->printlock);
	if (opt == 0)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d died\n", time, philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
		// free((philo - (philo->n - 1) * sizeof(philo)));
		// free(philo->philos_start);
		exit(-1); // alle threads beenden sich... data races werden weniger..komisch
		// pthread_exit(NULL); // soll angeblich safer sein und sachen freigeben... data races mehr.. und nicht alle threads werden beendet
	}
	else if (opt == 1)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is thinking\n", time, philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
	}
	else if (opt == 2)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is eating\n", time, philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
	}
	else if (opt == 3)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d is sleeping\n", time, philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
	}
	else if (opt == 4)
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("%d %d has taken a fork\n", time, philo->n);
		pthread_mutex_unlock(&philo->data->printlock);
	}
	else
	{
		pthread_mutex_lock(&philo->data->printlock);
		printf("(printmsg) - Error, wrong option");
		pthread_mutex_unlock(&philo->data->printlock);
	}
	prevtime = time;
}

void	*t_philosopher(void *param)
{
	t_philo	*philo = (t_philo *)param;

	if (philo->numofphilos == 1)
	{
		usleep(philo->timetodie * 1000);
		printf("%d %d died\n", get_time(philo->start_time), philo->n);
		return (NULL);
	}

	while (1) // flag fuer death
	{
	// think
		printmsg(philo, thinking);
	// eat
		pthread_mutex_lock(&philo->fork);
		printmsg(philo, forking);
		pthread_mutex_lock(philo->right_fork);
		printmsg(philo, forking);
		printmsg(philo, eating);
		philo->life = philo->timetodie;
		// philo->life -= philo->timetoeat;
		//if life<timetodie -> die
		usleep(philo->timetoeat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->fork);

	// sleep
		printmsg(philo, sleeping);
		usleep(philo->timetosleep * 1000);
	}

	return (NULL);
}

// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	static t_data	data;
	static t_philo	*philos;
	int				i;

	// int sleeptime = 1000;

	if (argc == 5 || argc == 6)
	{
		data.start_time = current_time();
		data.numofphilos = ft_atoi(argv[1]);
		data.timetodie = ft_atoi(argv[2]);
		data.timetoeat = ft_atoi(argv[3]);
		data.timetosleep = ft_atoi(argv[4]);
		if (argc == 6)
			data.maxmeals = ft_atoi(argv[5]);
		pthread_mutex_init(&data.printlock, NULL);
		philos = malloc(data.numofphilos * sizeof(t_philo));
		i = -1;
		while (++i < data.numofphilos)
		{
			philos[i].start_time = data.start_time;
			philos[i].numofphilos = data.numofphilos;
			if (argc == 6)
				philos[i].maxmeals = data.maxmeals;
			philos[i].timetodie = data.timetodie;
			philos[i].life = data.timetodie;
			philos[i].timetoeat = data.timetoeat;
			philos[i].timetosleep = data.timetosleep;
			philos[i].data = &data;
			philos[i].n = i + 1;
			philos[i].right_fork = &philos[(i + 1) % data.numofphilos].fork;
			// philos[i].philos_start = (t_philo*)philos;
		
			// if (i == data.numofphilos - 1)
			// 	philos[i].n = 1;
			// else
			// 	philos[i].n = i + 1;

			// printf("philos[i].n = %d\n", philos[i].n);
			pthread_mutex_init(&philos[i].fork, NULL);
		}
		i = -1;
		while (++i < data.numofphilos)
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
	// while (1)
	// 	printf("hi\n");

    // pthread_mutex_init(&data.lock, NULL);
    // pthread_mutex_destroy(&data.lock);
	free(philos);

	return (0);
}

// int	main(int argc, char **argv)
// {
// 	static t_data	data;
// 	static t_philo	*philos;

// 	int	i = -1;
// 	int sleeptime = 1000;

// 	if (argc == 4 || argc == 5)
// 	{
// 		data.start_time = current_time();
// 		data.numofphilos = ft_atoi(argv[1]);
// 		data.timetodie = ft_atoi(argv[2]);
// 		data.timetoeat = ft_atoi(argv[3]);
// 		data.timetosleep = ft_atoi(argv[4]);
// 		pthread_mutex_init(&data.printlock, NULL);
// 		philos = malloc(data.numofphilos * sizeof(t_philo));
// 		while (++i < data.numofphilos)
// 		{
// 			philos[i].start_time = data.start_time;
// 			philos[i].numofphilos = data.numofphilos;
// 			philos[i].timetodie = data.timetodie;
// 			philos[i].timetoeat = data.timetoeat;
// 			philos[i].timetosleep = data.timetosleep;
// 			philos[i].data = &data;
// 			philos[i].n = i + 1;
// 			pthread_mutex_init(&philos[i].fork, NULL);
// 		}
// 		i = -1;
// 		if (data.numofphilos % 2 == 0)
// 		{
// 			i = -1;
// 			while (++i < data.numofphilos)
// 			{
// 				if (i % 2 != 0)
// 				{
// 					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
// 						printf("\nThread can't be created");
// 				}
// 			}	
// 			usleep(sleeptime);
// 			i = -1;	
// 			while (++i < data.numofphilos)
// 			{
// 				if (i % 2 == 0)
// 				{
// 					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
// 						printf("\nThread can't be created");
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (pthread_create(&philos[0].tid, NULL, t_philosopher, &philos[0]) != 0)
// 				printf("\nThread can't be created");
// 			i = 0;
// 			usleep(sleeptime);
// 			while (++i < data.numofphilos)
// 			{
// 				if (i % 2 != 0)
// 				{
// 					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
// 						printf("\nThread can't be created");
// 				}
// 			}	
// 			usleep(sleeptime);
// 			i = 0;	
// 			while (++i < data.numofphilos)
// 			{
// 				if (i % 2 == 0)
// 				{
// 					if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
// 						printf("\nThread can't be created");
// 				}
// 			}
// 		}
// 		i = -1;
// 		while (++i < data.numofphilos)
//     		pthread_join(philos[i].tid, NULL);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
// 	}

//     // pthread_mutex_init(&data.lock, NULL);
//     // pthread_mutex_destroy(&data.lock);
// 	free(philos);

// 	return (0);
// }

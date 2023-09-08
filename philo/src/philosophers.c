/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 20:21:26 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 21:16:26 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	timetodie(t_philo *philo, int time)
{
	philo->life -= time - philo->prevtime;
	if (philo->data->deadflag)
	{
		if (philo->right_fork_flag)
			pthread_mutex_unlock(philo->right_fork);
		if (philo->fork_flag)
			pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->data->printlock);
		pthread_exit(NULL);
	}
	if (philo->life <= 0)
	{
		philo->data->deadflag = true;
		printf(RED "%d %d died\n" WHT, time, philo->n); //died2!!!
		timetodie(philo, time);
		return (1);
	}
	philo->prevtime = time;
	return (0);
}

void	printmsg(t_philo *philo, enum week opt)
{
	static int	time;

	timetodie(philo, time);
	time = get_time(philo->start_time);
	if (opt == 1)
		printf(MAG "%d %d is thinking\n" WHT, time, philo->n);
	else if (opt == 2)
		printf(GRN "%d %d is eating\n" WHT, time, philo->n);
	else if (opt == 3)
		printf(BLU "%d %d is sleeping\n" WHT, time, philo->n);
	else if (opt == 4)
		printf(YEL "%d %d has taken a fork\n" WHT, time, philo->n);
	else
		printf("(printmsg) - Error, wrong option");
}

void	*t_philosopher(void *param)
{
	size_t	time;

	t_philo	*philo = (t_philo *)param;
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
		if (philo->n % 2 == 0)
		{
			pthread_mutex_lock(&philo->fork);
			philo->fork_flag = true;
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			philo->right_fork_flag = true;
		}
		pthread_mutex_lock(&philo->data->printlock);
		printmsg(philo, forking);
		pthread_mutex_unlock(&philo->data->printlock);
		if (philo->n % 2 == 0)
		{
			pthread_mutex_lock(philo->right_fork);
			philo->right_fork_flag = true;
		}
		else
		{
			pthread_mutex_lock(&philo->fork);
			philo->fork_flag = true;
		}
		pthread_mutex_lock(&philo->data->printlock);
		printmsg(philo, forking);
		philo->life = philo->timetodie;
		printmsg(philo, eating);
		if (philo->maxmeals > 0)
		{
			philo->data->maxmeals--;
			philo->maxmeals--;
			if (philo->data->maxmeals <= 0)
				philo->data->deadflag = true;
		}
		pthread_mutex_unlock(&philo->data->printlock);
		usleep(philo->timetoeat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		philo->right_fork_flag = false;
		pthread_mutex_unlock(&philo->fork);
		philo->fork_flag = false;
		pthread_mutex_lock(&philo->data->printlock);
		printmsg(philo, sleeping);
		pthread_mutex_unlock(&philo->data->printlock);
		usleep(philo->timetosleep * 1000);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	static t_data	data;
	static t_philo	*philos;
	int				i;

	if (argc == 5 || argc == 6)
	{
		data.start_time = current_time();
		data.numofphilos = ft_atoi(argv[1]);
		data.timetodie = ft_atoi(argv[2]);
		data.timetoeat = ft_atoi(argv[3]);
		data.timetosleep = ft_atoi(argv[4]);
		if (argc == 6)
			data.maxmeals = ft_atoi(argv[5]) * data.numofphilos;
		pthread_mutex_init(&data.printlock, NULL);
		pthread_mutex_init(&data.deadlock, NULL);
		philos = ft_calloc(data.numofphilos, sizeof(t_philo));
		i = -1;
		while (++i < data.numofphilos)
		{
			philos[i].start_time = data.start_time;
			philos[i].numofphilos = data.numofphilos;
			if (argc == 6)
				philos[i].maxmeals = data.maxmeals / data.numofphilos;
			philos[i].timetodie = data.timetodie;
			philos[i].life = data.timetodie;
			philos[i].timetoeat = data.timetoeat;
			philos[i].timetosleep = data.timetosleep;
			philos[i].data = &data;
			philos[i].n = i + 1;
			philos[i].right_fork = &philos[(i + 1) % data.numofphilos].fork;
			pthread_mutex_init(&philos[i].fork, NULL);
		}
		i = -1;
		if (data.numofphilos % 2 != 0)
		{
			i = 0;
			if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
					printf("\nThread can't be created");
		}
		while (++i < data.numofphilos)
		{
			if (i % 2 == 0)
				if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
					printf("\nThread can't be created");
		}	
		i = -1;
		while (++i < data.numofphilos)
		{
			if (i % 2 != 0)
				if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
					printf("\nThread can't be created");
		}
		i = -1;
		while (++i < data.numofphilos)
    		pthread_join(philos[i].tid, NULL);
	}
	else
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	pthread_mutex_destroy(&data.deadlock);
	pthread_mutex_destroy(&data.printlock);
	free(philos);
	return (0);
}

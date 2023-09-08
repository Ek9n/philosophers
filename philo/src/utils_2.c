/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:41:19 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 22:27:53 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_time(int start_time)
{
	return (current_time() - start_time);
}

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
		printf(RED "%d %d died\n" WHT, time, philo->n);
		timetodie(philo, time);
		return (1);
	}
	philo->prevtime = time;
	return (0);
}

void	printmsg(t_philo *philo, enum e_week opt)
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

void	f_forking(t_philo *philo)
{
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
}

void	f_eating(t_philo *philo)
{
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
}

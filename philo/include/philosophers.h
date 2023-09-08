/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:18:27 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 22:27:52 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <stdbool.h>
# include "./colors.h"

enum e_week
{
	dieing,
	thinking,
	eating,
	sleeping,
	forking
};

typedef struct data
{
	int				start_time;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				numofphilos;
	int				maxmeals;	
	bool			deadflag;
	int				deadtime;
	pthread_mutex_t	printlock;
	pthread_mutex_t	msglock;
	pthread_mutex_t	deadlock;
}	t_data;

typedef struct philosopher
{
	int				pretime_check;
	int				prevtime;
	int				life;
	int				start_time;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				numofphilos;
	int				maxmeals;	
	int				n;
	bool			fork_flag;
	bool			right_fork_flag;
	pthread_t		tid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);
int		ft_atoi(const char *str);
int		current_time(void);
int		get_time(int start_time);
void	printmsg(t_philo *philo, enum e_week opt);
int		timetodie(t_philo *philo, int time);
void	f_forking(t_philo *philo);
void	f_eating(t_philo *philo);
void	f_sleeping(t_philo *philo);
void	*t_philosopher(void *param);
void	init_data(t_data *data, int argc, char **argv);
void	init_philos(t_philo *philos, t_data *data, int argc, int i);
void	create_philos_1(t_philo *philos, t_data *data);
void	create_philos_2(t_philo *philos, t_data *data);

#endif

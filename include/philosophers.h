/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:18:27 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 13:19:27 by hstein           ###   ########.fr       */
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

enum week{dieing, thinking, eating, sleeping, forking};

typedef struct	data
{
	int				start_time;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				numofphilos;
	int				maxmeals;	
	bool			deadflag;
	int				deadtime; //zeit hier vorher checken als deadtime und spaeter ausprinten
	pthread_mutex_t	printlock;
	pthread_mutex_t	msglock;
	pthread_mutex_t	deadlock;
} t_data;

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
	// bool			maxmeals_flag;
	pthread_t		tid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	// void			*philos_start;

} t_philo;


void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);
int		ft_atoi(const char *str);
int		current_time(void);
int		get_time(int start_time);
void	printmsg(t_philo *philo, enum week opt);
int		timetodie(t_philo *philo, int time, int opt);

// int		lapsed_time(t_data *data);

#endif

// cc src/philo.c src/utils.c && ./a.out 5 2 3 4
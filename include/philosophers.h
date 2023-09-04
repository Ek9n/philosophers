/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:18:27 by hstein            #+#    #+#             */
/*   Updated: 2023/09/04 05:13:00 by hstein           ###   ########.fr       */
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

enum week{dieing, thinking, eating, sleeping, forking};

typedef struct	data
{
	int				start_time;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				numofphilos;
	int				maxmeals;	
	pthread_mutex_t	printlock;
} t_data;

typedef struct philosopher
{	
	int				life;
	int				start_time;
	int				timetodie;
	int				timetoeat;
	int				timetosleep;
	int				numofphilos;
	int				maxmeals;	
	int				n;
	pthread_t		tid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;

} t_philo;


void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		current_time(void);
int		get_time(int start_time);
// int		lapsed_time(t_data *data);

#endif

// cc src/philo.c src/utils.c && ./a.out 5 2 3 4
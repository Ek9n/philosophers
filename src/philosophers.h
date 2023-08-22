/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:18:27 by hstein            #+#    #+#             */
/*   Updated: 2023/08/22 22:17:06 by hstein           ###   ########.fr       */
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

typedef struct	data
{
	int				numofphilos;
	int				numofphilo;
	// t_philo			*nphilos;
	pthread_mutex_t	lock;
} t_data;

typedef struct philosopher
{
	pthread_t	tid;
	int			n;
	t_data		*data;

} t_philo;


#endif

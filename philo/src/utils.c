/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 22:41:19 by hstein            #+#    #+#             */
/*   Updated: 2023/09/08 17:56:26 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		write(fd, &s[i++], 1);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*s;

	s = (void *) malloc(num * size);
	if (s == NULL)
		return (0);
	else
	{
		ft_bzero(s, num * size);
		return (s);
	}
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		res;
	int		i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] != '\0' && ((9 <= str[i] && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	get_time(int start_time)
{
	return (current_time() - start_time);
}

size_t	lapsed_time(size_t prevtime, int start_time, bool reset)
{
	long		time;

	if (reset)
	{
		prevtime = 0;
		return (0);
	}
	time = get_time(start_time);
	if (prevtime == 0)
		prevtime = time;
	return (time - prevtime);
}

int	remote_delay_ms(size_t delay)
{
	size_t			time_us;
	static size_t	time_tmp;
	static size_t	time_cnt;
	struct timeval	tv;

	delay *= 1000;
	gettimeofday(&tv, NULL);
	time_us = tv.tv_usec;
	if (time_tmp > time_us)
		time_cnt += 1000000 - time_tmp + time_us;
	else
		time_cnt += time_us - time_tmp;
	time_tmp = time_us;
	if ((time_cnt % (delay * 2)) < delay)
		return (1);
	return (0);
}

size_t	delay_ms(int reset)
{
	static bool		flag;
	static size_t	counter;
	size_t			delay;

	if (reset)
	{
		counter = 0;
		return (0);
	}
	delay = 10;
	if (remote_delay_ms(delay))
		flag = true;
	if (flag == true && !remote_delay_ms(delay))
	{
		counter += 50;
		flag = false;
	}
	return (counter);
}
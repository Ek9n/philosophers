
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


void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		write(fd, &s[i++], 1);
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

void	*t_philosopher(void *wert)
{
	pthread_mutex_lock(&lock);
	for(int i = 0; i < 20; i++)
	{
		printf("philo_works[%d]\n", *((int *)wert));
	}
	pthread_mutex_unlock(&lock);

	return (NULL);
}
// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{

	if (argc == 4 || argc == 5)
	{
		int	error;
		int n[] = {1, 2};

		tid = malloc(2 * sizeof(int));

        error = pthread_create(tid, NULL, t_philosopher, &n[0]);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));
        error = pthread_create(&tid[1], NULL, t_philosopher, &n[1]);
        if (error != 0)
            printf("\nThread can't be created : [%s]", strerror(error));

    	pthread_join(*tid, NULL);
		pthread_join(*(tid + 1), NULL);
	}
	else
	{
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	}
	free(tid);
	return (0);
}

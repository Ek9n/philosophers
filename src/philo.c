
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
	// pthread_mutex_lock(&philo->data->lock);
	// printf("numofphilo=%d\n", data->numofphilo);
	for(int i = 0; i < 1; i++)
	{
		printf("philosopher%d\n", philo->n);
		printf("id=%lu\n", philo->tid);
	}
	// pthread_mutex_unlock(&philo->data->lock);
	return (NULL);
}

// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	static t_data	data;
	static t_philo	*philos;

	int	i = -1;

	if (argc == 4 || argc == 5)
	{
		data.numofphilos = ft_atoi(argv[1]);
		printf("numofphilos=%d\n\n", data.numofphilos);

		philos = malloc(data.numofphilos * sizeof(t_philo));
		while (++i < data.numofphilos)
		{
			philos[i].data = &data;
			philos[i].n = i + 1;
		}
        pthread_mutex_init(&data.lock, NULL);
		int	i = -1;
		while(++i < data.numofphilos)
		{
			// data.numofphilo = i;
        	if (pthread_create(&philos[i].tid, NULL, t_philosopher, &philos[i]) != 0)
           		printf("\nThread can't be created");
			// printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!i=%d\n", i);
		}
		i = -1;
		while (++i < data.numofphilos)
    		pthread_join(philos[i].tid, NULL);
	}
	else
	{
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	}

    // pthread_mutex_destroy(&data.lock);
	free(philos);

	return (0);
}


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

void	*t_philosopher(void *param)
{
	struct philosophers	*vars = (struct philosophers *)param;
	pthread_mutex_lock(&vars->lock);
	int n = vars->numofphilo;
	// printf("numofphilo=%d\n", vars->numofphilo);
	for(int i = 0; i < 1; i++)
	{
		printf("philosopher%d\n", n + 1);
		printf("id=%lu\n", vars->nphilos[n].tid);
	}
	pthread_mutex_unlock(&vars->lock);
	return (NULL);
}

// int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep int[number_of_times_each_philosopher_must_eat]
int	main(int argc, char **argv)
{
	static struct philosophers	vars;
	int	i = 0;

	if (argc == 4 || argc == 5)
	{
		vars.numofphilos = ft_atoi(argv[1]);
		printf("numofphilos=%d\n\n", vars.numofphilos);

		vars.nphilos = malloc(vars.numofphilos * sizeof(t_philo));
		
        pthread_mutex_init(&vars.lock, NULL);

		while(i < vars.numofphilos)
		{
			vars.numofphilo = i;
        	if (pthread_create(&vars.nphilos[i].tid, NULL, t_philosopher, &vars) != 0)
           		printf("\nThread can't be created");
			// printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!i=%d\n", i);
			i++;
		}
		i = 0;
    		// pthread_join(vars.nphilos[i].tid, NULL);
		while (1);
	}
	else
	{
		ft_putstr_fd("(main)Error - wrong num of args\n", 2);
	}

    // pthread_mutex_destroy(&vars.lock);
	free(vars.nphilos);

	return (0);
}

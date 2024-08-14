#include "philo.h"

static t_mtx	*init_fork_mtxs(t_data *data)
{
	t_mtx	*fork;
	unsigned int	i;

	fork = malloc(sizeof(t_mtx) * data->nbr_of_philos);
	if (!fork)
		return (handle_err(ERR_MUTEX, data));
	memset(fork, 0, sizeof(t_mtx) * data->nbr_of_philos);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (handle_err(ERR_MUTEX, data));
		i++;
	}
	return (fork);
}

static bool	init_mtxs(t_data *data)
{
	data->fork_mtx = init_fork_mtxs(data);
	if (!(data->fork_mtx))
		return (false);
	if (pthread_mutex_init(&data->dinner_mtx, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->print_mtx, NULL) != 0)
		return (false);
	return (true);
}

static void	fork_dist(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nbr_of_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->table->nbr_of_philos;
		philo->fork[1] = philo->id;
	}
}

static t_philo	**init_philo(t_data *data)
{
	unsigned int	i;
	t_philo			**philos;

	philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!philos)
		return (handle_err(ERR_MALLOC, data));
	memset(philos, 0, sizeof(t_philo) * data->nbr_of_philos);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
			return (handle_err(ERR_MALLOC, data));
		memset(philos[i], 0, sizeof(t_philo));
		philos[i]->id = i;
		philos[i]->table = data;
		fork_dist(philos[i]);
		if (pthread_mutex_init(&philos[i]->last_meal_mtx, NULL) != 0)
			return (handle_err(ERR_MALLOC, data));
		if (pthread_mutex_init(&philos[i]->meal_death_mtx, NULL) != 0)
			return (handle_err(ERR_MALLOC, data));
		i++;
	}
	return (philos);
}

t_data	*init_data(int ac, char **av, int i)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (handle_err(ERR_MALLOC, 0));
	memset(data, 0, sizeof(t_data));
	data->nbr_of_philos = ft_atoi(av[i++]);
	data->time_to_die = ft_atoi(av[i++]);
	data->time_to_eat = ft_atoi(av[i++]);
	data->time_to_sleep = ft_atoi(av[i++]);
	if (ac == 6)
		data->meals_total = ft_atoi(av[i]);
	else
		data->meals_total = -1;
	data->philo_died = false;
	data->all_full = false;
	if (!init_mtxs(data))
		return (handle_err(ERR_MUTEX, data));
	data->philos = init_philo(data);
	if (!data->philos)
		return (handle_err(ERR_MALLOC, data));
	return (data);
}
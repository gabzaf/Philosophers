#include "philo.h"

static int init_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_simulation = get_time();
	while(++i < data->nbr_of_philos)
	{
		if (pthread_create(&data->arr_philos[i]->thread, NULL, routine, data->arr_philos[i]))
			return (1);
	}
	return (0);
}

static int init_forks(t_data *data)
{
	int	i;
	t_fork	*arr_forks;

	arr_forks = data->arr_forks;
	i = 0;
	while (i < data->nbr_of_philos)
	{
		//testar mutex_init
		if (pthread_mutex_init(&arr_forks[i].fork, NULL))
			return (1);
		arr_forks[i].fork_id = i + 1;
		i++;
	}
	data->arr_forks = arr_forks;
	return (0);
}
static int	philos_init(t_data *data)
{
	int	i;
	t_philo	*philo;

	i = data->nbr_of_philos;
	while (--i >= 0)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i;
		philo->is_full = false;
		philo->nbr_eats = 0;
		philo->last_eat = 0;
		philo->thread = 0;
		philo->left_fork = &data->arr_forks[i];
		philo->right_fork = &data->arr_forks[((i + 1) % data->nbr_of_philos)];
		philo->table = data;
		data->arr_philos[i] = philo;
	}
	return (0);
}

int	init(t_data *data)
{
	if (philos_init(data))
		return (1);
	if (init_forks(data))
		return (2);
	if (init_threads(data))
		return (3);
	return (0);
}

#include "philo.h"

static void	cleaning_philos(t_philo **philo, t_data *data)
{
	unsigned int	i;

	i = 0;
	while (philo[i] && i < data->nbr_of_philos)
	{
		pthread_mutex_destroy(&(data->fork_mtx[i]));
		pthread_mutex_destroy(&(data->philos[i]->last_meal_mtx));
		pthread_mutex_destroy(&(data->philos[i]->meal_death_mtx));
		free(philo[i]);
		i++;
	}
	free(data->fork_mtx);
	free(philo);
}

void	dealloc_and_destroy(t_data *data)
{
	if (data->philos)
	{
		cleaning_philos(data->philos, data);
		pthread_mutex_destroy(&(data->print_mtx));
		pthread_mutex_destroy(&(data->dinner_mtx));
	}
	if (data)
		free(data);
}

int	msg(char *str, int exit_nbr)
{
	printf("%s", str);
	return (exit_nbr);
}

void	*handle_err(char *str, t_data *data)
{
	if (data != NULL)
		dealloc_and_destroy(data);
	msg(str, EXIT_FAILURE);
	return (NULL);
}

int	handle_err_alt(char *str, t_data *data)
{
	if (data != NULL)
		dealloc_and_destroy(data);
	return (msg(str, 0));
}
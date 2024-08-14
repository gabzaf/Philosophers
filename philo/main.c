#include "philo.h"

static bool	dinner_done(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_join(data->philos[i]->thread_id, NULL) != 0)
			return (handle_err_alt(ERR_THREAD, data));
		i++;
	}
	if (pthread_join(data->monitor, NULL) != 0)
		return (handle_err_alt(ERR_THREAD, data));
	dealloc_and_destroy(data);
	return (true);
}

static bool	start_dinner(t_data *data)
{
	unsigned int	i;

	data->start_time = get_time() + (data->nbr_of_philos * 20);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		if (pthread_create(&data->philos[i]->thread_id, \
			NULL, &routine, data->philos[i]) != 0)
			return (handle_err_alt(ERR_THREAD, data));
		i++;
	}
	if (pthread_create(&data->monitor, NULL, &end_sim_mntr, \
			data) != 0)
		return (handle_err_alt(ERR_THREAD, data));
	return (dinner_done(data));
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_args(ac, av))
		return (1);
	data = init_data(ac, av, 1);
	if (!data)
		return (2);
	if (!start_dinner(data))
		return (3);
	return (0);
}
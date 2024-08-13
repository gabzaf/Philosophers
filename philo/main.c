#include "philo.h"

static int	run_threads(t_data *data)
{
	int	i;
	int	r;
	
	i = -1;
	while (++i < data->nbr_of_philos)
	{
		r = pthread_join(data->arr_philos[i]->thread, NULL);
		if (r)
			return (r);
	}
		return (r);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_args(av) || init_data(&data, av))
			return (1);
		init(&data);
		monitor_routine(&data);
		if (run_threads(&data))
			return (2);
		free_all(&data);
	}
	else
		print_error(ac);
	return (0);
}
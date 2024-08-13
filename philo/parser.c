#include "philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (c);
	else
		return (0);
}

static int	check_limits(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i++]) > 2147483647)
			return (1);
	}
	return (0);
}

static int	check_input_digit(char **argv)
{
	int	i;
	int	j;
	
	i = 0;
	while(argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			//conferir no subject se aceito sinal de +
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+')
				return (1);
			j++;
		}
	i++;
	}
	return (0);
}

int	check_args(char **argv)
{
	argv++;
	if (check_input_digit(argv) || check_limits(argv))
	{
		printf("Parse error: Incorrect INPUT.\n");
		return (-1);
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nbr_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argv[5])
		data->eats_total = ft_atol(argv[5]);
	else
		data->eats_total = - 1;
	data->is_all_alive = true;
	data->count_full = 0;
	data->start_simulation = get_time();
	if (pthread_mutex_init(&data->mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->print_mtx, NULL))
		return (1);
	data->arr_forks = malloc(sizeof(t_fork) * data->nbr_of_philos);
	data->arr_philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	if (!data->arr_forks || !data->arr_philos)
		return (1);
	return (0);
}

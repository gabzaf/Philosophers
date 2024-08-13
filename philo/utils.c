#include "philo.h"

void	print_status(t_philo *p, t_status flag)
{
	long long	now;
	t_data		*table;

	table = p->table;
	pthread_mutex_lock(&table->print_mtx);
	now = get_time() - table->start_simulation;
	if (flag == DEAD)
		printf("%lld %d died\n", now, p->id + 1);
	pthread_mutex_lock(&table->mutex);
	if (!table->is_all_alive)
	{
		pthread_mutex_unlock(&table->mutex);
		pthread_mutex_unlock(&table->print_mtx);
		return ;
	}
	pthread_mutex_unlock(&table->mutex);
	if (flag == SLEEP)
		printf ("%lld %d is sleeping\n", now, p->id + 1);
	if (flag == THINK)
		printf ("%lld %d is thinking\n", now, p->id + 1);
	if (flag == EAT)
		printf ("%lld %d is eating\n", now, p->id + 1);
	if (flag == FORK)
		printf ("%lld %d has taken a fork\n", now, p->id + 1);
	pthread_mutex_unlock(&table->print_mtx);
}

void	free_all(t_data *data)
{
	int	i;

	i = data->nbr_of_philos;
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->print_mtx);
	while (--i >= 0)
	{
		pthread_mutex_destroy(&data->arr_forks[i].fork);
		free(data->arr_philos[i]);
	}
	free(data->arr_forks);
	free(data->arr_philos);
}

long	ft_atol(const char *str)
{
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		r *= 10;
		r += *str++ - '0';
	}
	return ((long)(r * sign));
}

void	print_error(int argc)
{
	if (argc < 5)
		printf("Not enough args\n");
	else if (argc >6)
		printf("Too many args\n");
}

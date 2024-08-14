#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	check_and_wait(t_data *data, t_philo *philo, long time)
{
	long long	i;
	bool		any_death;

	i = get_time();
	while (get_time() - i < time && !(end_sim(philo)))
	{
		pthread_mutex_lock(&data->dinner_mtx);
		any_death = data->philo_died;
		pthread_mutex_unlock(&data->dinner_mtx);
		if (any_death)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *str)
{
	bool		any_death;

	pthread_mutex_lock(&philo->table->print_mtx);
	any_death = philo->table->philo_died;
	if (any_death)
	{
		pthread_mutex_unlock(&philo->table->print_mtx);
		return ;
	}
	printf("%ld ", get_time() - philo->table->start_time);
	printf("%d ", philo->id);
	printf("%s\n", str);
	pthread_mutex_unlock(&philo->table->print_mtx);
	return ;
}

bool	is_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

long int	ft_atoi(char *str)
{
	long int	num;

	num = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - 48;
		str++;
	}
	return (num);
}
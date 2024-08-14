#include "philo.h"

bool	end_sim(t_philo *philo)
{
	bool	philo_full;
	bool	death;

	pthread_mutex_lock(&philo->table->dinner_mtx);
	death = philo->table->philo_died;
	pthread_mutex_unlock(&philo->table->dinner_mtx);
	if (death)
		return (true);
	pthread_mutex_lock(&philo->meal_death_mtx);
	philo_full = philo->is_full;
	pthread_mutex_unlock(&philo->meal_death_mtx);
	if (philo_full)
		return (true);
	return (false);
}

static bool	death_checker(t_data *data, t_philo **philo)
{
	unsigned int	i;
	bool			philo_full;
	long			time_hungry;

	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&philo[i]->last_meal_mtx);
		pthread_mutex_lock(&philo[i]->meal_death_mtx);
		philo_full = philo[i]->is_full;
		time_hungry = get_time() - philo[i]->last_meal;
		pthread_mutex_unlock(&philo[i]->last_meal_mtx);
		pthread_mutex_unlock(&philo[i]->meal_death_mtx);
		if (!philo_full && time_hungry >= data->time_to_die)
		{
			pthread_mutex_lock(&data->dinner_mtx);
			print_status(philo[i], "died");
			data->philo_died = true;
			pthread_mutex_unlock(&data->dinner_mtx);
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	meal_done_checker(t_data *data, t_philo **philo)
{
	unsigned int	i;
	bool			philo_full;

	if (data->meals_total == -1)
		return (false);
	i = 0;
	while (i < data->nbr_of_philos)
	{
		pthread_mutex_lock(&philo[i]->meal_death_mtx);
		philo_full = philo[i]->is_full;
		pthread_mutex_unlock(&philo[i]->meal_death_mtx);
		if (!philo_full)
			return (false);
		i++;
	}
	if (i == data->nbr_of_philos)
	{
		pthread_mutex_lock(&data->dinner_mtx);
		data->all_full = true;
		pthread_mutex_unlock(&data->dinner_mtx);
		return (true);
	}
	return (false);
}

void	*end_sim_mntr(void *dt)
{
	t_data	*data;
	bool	any_death;
	t_philo	**philo;
	int		i;
	time_t	start;

	i = 0;
	data = (t_data *)dt;
	philo = data->philos;
	pthread_mutex_lock(&data->dinner_mtx);
	start = data->start_time;
	any_death = data->philo_died;
	pthread_mutex_unlock(&data->dinner_mtx);
	while (get_time() < start)
		continue ;
	if (any_death)
		return (NULL);
	while (!(meal_done_checker(data, philo)))
	{
		i++;
		if (death_checker(data, philo))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

void	sync_start(t_philo *philo)
{
	long	start;

	pthread_mutex_lock(&philo->table->dinner_mtx);
	start = philo->table->start_time;
	pthread_mutex_unlock(&philo->table->dinner_mtx);
	while (get_time() < start)
		continue ;
}
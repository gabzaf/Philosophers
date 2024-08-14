#include "philo.h"

static void	think(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dinner_mtx);
	if (philo->table->all_full)
	{
		pthread_mutex_unlock(&philo->table->dinner_mtx);
		return ;
	}
	print_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->table->dinner_mtx);
}

static void	nap(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dinner_mtx);
	print_status(philo, "is sleeping");
	if (philo->table->all_full)
	{
		pthread_mutex_unlock(&philo->table->dinner_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->table->dinner_mtx);
	check_and_wait(philo->table, philo, philo->table->time_to_sleep);
	usleep(100);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mtx[philo->fork[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_mtx[philo->fork[1]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = get_time();
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->last_meal_mtx);
	check_and_wait(philo->table, philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->fork_mtx[philo->fork[0]]);
	pthread_mutex_unlock(&philo->table->fork_mtx[philo->fork[1]]);
	pthread_mutex_lock(&philo->meal_death_mtx);
	philo->nbr_of_meals++;
	if (philo->nbr_of_meals == philo->table->meals_total)
		philo->is_full = true;
	pthread_mutex_unlock(&philo->meal_death_mtx);
}

void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_mtx[philo->fork[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->fork_mtx[philo->fork[0]]);
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->meals_total == 0)
		return (NULL);
	if (philo->table->time_to_die == 0)
		return (NULL);
	pthread_mutex_lock(&philo->last_meal_mtx);
	philo->last_meal = philo->table->start_time;
	pthread_mutex_unlock(&philo->last_meal_mtx);
	sync_start(philo);
	if (philo->table->nbr_of_philos == 1)
		return (one_philo(philo));
	else if (philo->id % 2 == true)
		usleep(500);
	while (!end_sim(philo))
	{
		eat(philo);
		if (!end_sim(philo))
			nap(philo);
		if (!end_sim(philo))
			think(philo);
	}
	return (NULL);
}
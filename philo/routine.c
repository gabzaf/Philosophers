#include "philo.h"

static void get_forks(t_fork **first_fork, t_fork **second_fork, t_philo *philo)
{
    if (philo->left_fork->fork_id < philo->right_fork->fork_id)
    {
        *first_fork = philo->left_fork;
        *second_fork = philo->right_fork;
    }
    else
    {
        *first_fork = philo->right_fork;
        *second_fork = philo->left_fork;
    }
}

static int  eat(t_philo *philo, t_data *table)
{
    t_fork  *first_fork;
    t_fork  *second_fork;

    get_forks(&first_fork, &second_fork, philo);
    pthread_mutex_lock(&first_fork->fork);
    print_status(philo, FORK);
    if (table->nbr_of_philos == 1)
        return (1);
    pthread_mutex_lock(&second_fork->fork);
    print_status(philo, FORK);
    print_status(philo, EAT);
    pthread_mutex_lock(&table->mutex);
    philo->nbr_eats++;
    philo->last_eat = get_time() - table->start_simulation;
    pthread_mutex_unlock(&table->mutex);
    smart_sleep(table, table->time_to_eat);
    pthread_mutex_unlock(&first_fork->fork);
    pthread_mutex_unlock(&second_fork->fork);
    return (0);
}

static void nap(t_philo *philo, t_data *table)
{
    print_status(philo, SLEEP);
    smart_sleep(table, table->time_to_sleep);
}

static void think(t_philo *philo)
{
    print_status(philo, THINK);
}

void    *routine(void *arg)
{
    t_philo *p;
    t_data  *tab;

    p = (t_philo *)arg;
    tab = p->table;
    if (p->id %2)
        usleep(1500);
    while (check_all_alive(tab) && tab->count_full != tab->nbr_of_philos)
    {
        if (eat(p, tab))
            return (NULL);
        nap(p, tab);
        think(p);
    }
    return (NULL);
}
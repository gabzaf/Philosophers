#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t t_mtx;
typedef pthread_t	t_thread;
typedef struct s_data	t_data;

typedef enum	e_status
{
	SLEEP,
	EAT,
	FORK,
	THINK,
	DEAD
}	t_status;

typedef struct	s_fork
{
	t_mtx	fork;
	int	fork_id;
}	t_fork;

typedef struct s_philo
{
	int	id; //mudei aqui
	bool	is_full;
	int	nbr_eats;
	int	last_eat;
	t_thread	thread;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_data	*table;
}	t_philo;

typedef struct s_data
{
	long	nbr_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	eats_total;
	long	count_full;
	long	start_simulation;
	bool	is_all_alive;
	t_mtx	mutex;
	t_mtx	print_mtx;
	t_fork	*arr_forks;
	t_philo	**arr_philos;
}	t_data;

int	check_args(char **argv);
int	init_data(t_data *data, char **argv);
long long	get_time(void);
long	ft_atol(const char *str);
int	init(t_data *data);
void    *routine(void *arg);
int monitor_routine(t_data *data);
void	free_all(t_data *data);
void	print_error(int argc);
void	print_status(t_philo *p, t_status flag);
void	smart_sleep(t_data *t, long long time);
bool	check_all_alive(t_data *data);


#endif

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <string.h>

typedef struct s_data	t_data;
typedef struct s_philo t_philo;
typedef pthread_t	t_thread;
typedef pthread_mutex_t t_mtx;

typedef struct s_philo
{
	int				id;
	bool			is_full;
	int				nbr_of_meals;
	long			last_meal;
	bool			dead;
	unsigned int	fork[2];
	t_thread		thread_id;
	t_mtx			last_meal_mtx;
	t_mtx			meal_death_mtx;
	t_data			*table;
}	t_philo;

typedef struct s_data
{
	unsigned int	nbr_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_total;
	long			start_time;
	bool			all_full;
	bool			philo_died;
	t_thread		monitor;
	t_mtx			*fork_mtx;
	t_mtx			dinner_mtx;
	t_mtx			print_mtx;
	t_philo			**philos;
}	t_data;

# define INPUT_ERROR "ERROR: Input wrong format\n"
# define ERR_MALLOC "ERROR: Memory allocation error\n"
# define ERR_MUTEX "ERROR: Mutex error\n"
# define ERR_THREAD "ERROR: Thread error\n"

bool		check_args(int ac, char **av);
long int	ft_atoi(char *str);
bool		is_space(char c);
t_data		*init_data(int ac, char **av, int i);
int			msg(char *str, int exit_nbr);
void		*handle_err(char *str, t_data *data);
void		dealloc_and_destroy(t_data *data);
long		get_time(void);
void		*routine(void *data);
bool		end_sim(t_philo *philo);
void		sync_start(t_philo *philo);
void		print_status(t_philo *philo, char *str);
void		*end_sim_mntr(void *data);
int			handle_err_alt(char *str, t_data *data);
void		check_and_wait(t_data *data, t_philo *philo, long time);

#endif
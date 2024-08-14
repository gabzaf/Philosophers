#include "philo.h"

static bool	check_limit(char *str)
{
	if (ft_atoi(str) > 2147483647)
		return (false);
	return (true);
}

static bool	is_pos_nbr(char *str)
{
	if (*str == '\0')
		return (false);
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str && *str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

bool	check_args(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (msg(INPUT_ERROR, false));
	i = 0;
	while (++i < ac)
	{
		if (!is_pos_nbr(av[i]))
			return (msg(INPUT_ERROR, false));
		if (!check_limit(av[i]))
			return (msg(INPUT_ERROR, false));
		if (i == 1 && ft_atoi(av[i]) == 0)
			return (msg(INPUT_ERROR, false));
	}
	return (true);
}
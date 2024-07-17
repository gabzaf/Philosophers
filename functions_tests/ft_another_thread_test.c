#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	*my_turn(void *arg)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		sleep(2);
		printf("My turn! %d\n", i);
		i++;
	}
	return (NULL);
}

void	your_turn()
{
	int	i;

	i = 0;
	while (i < 3)
	{
		sleep(1);
		printf("Your turn! %d\n", i);
		i++;
	}
}

int	main()
{
	pthread_t	new_thread;

	pthread_create(&new_thread, NULL, my_turn,NULL);
	your_turn();
	pthread_join(new_thread, NULL);
	return (0);
}

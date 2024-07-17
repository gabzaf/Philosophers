#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void	*my_turn(void *arg)
{
	int	i;
	int	*input = (int *)malloc(sizeof(int));
	
	*input = 5;
	i = 0;
	while (i < 8)
	{
		sleep(1);
		printf("My turn! %d %d\n", i, *input);
		i++;
		(*input)++;
	}
	return (input);
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
	int	*result;

	pthread_create(&new_thread, NULL, my_turn, NULL);
	your_turn();
	pthread_join(new_thread, (void *)&result);
	printf("result: %d\n", *result);
	return (0);
}


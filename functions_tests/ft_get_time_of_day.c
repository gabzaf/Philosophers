#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdint.h>

//1 second = 1.000 miliseconds

void	example()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return ;
	printf("%ld seconds\n", time.tv_sec);
	printf("%ld microseconds\n", time.tv_usec);
	printf("%ld years passed since 1970\n\n", time.tv_sec/60/60/24/365);
	//(n_of_scnds / 60 scnds / 60 mnts / 24 hrs / 365 days)
}

//Returns time in milliseconds
uint64_t	get_time() 
{
	struct timeval	time;

	if(gettimeofday(&time, NULL))
		return (0);
	return (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
}

void	scnd_example()
{
	uint64_t	start_time;
	uint64_t	now;

	start_time = get_time();
	//10.000 microseconds or 10 milliseconds
	usleep(10000);
	usleep(10000);
	//usleep(10000);
	now = get_time();
	printf("%ld milliseconds passed since the start\n", now - start_time);
}

int	main()
{
	//example();
	scnd_example();
	return (0);
}

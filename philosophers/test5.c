# include "includes/philosophers.h"

int	main(int ac, char **av)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	int start = (time.tv_sec * 1000) + (time.tv_usec / 1000);

	usleep(1001000);//this time will be time to sleep/eat/think

	gettimeofday(&time, 0);
	int finish = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	finish -= start;
	printf("%d ms\n", finish);

	return (0);
}
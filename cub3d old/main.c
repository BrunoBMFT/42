#include "includes/cub3d.h"
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

float conv(float n)//degrees to radians
{
	return (n * M_PI / 180);
}

int	main(void)
{
	float n1, n2;
	float an1, an2;

	an1 = 90;
	an2 = 181;
	n1 = sin(conv(an1));
	n2 = sin(conv(an2));
	printf("%lf %lf\n", n1, n2);
	n1 = cos(conv(an1));
	n2 = cos(conv(an2));
	printf("%lf %lf\n", n1, n2);
}
#include "../includes/cub3d.h"

void	angle_correct(double *angle, int *dir, bool is_h)
{
	while (*angle < 0)
		*angle += 360;
	while (*angle >= 360)
		*angle -= 360;
	if (is_h)
	{
		*angle = 180 - *angle;
		if (*angle >= 0 && *angle <= 180)
			*dir = 1;
		else
			*dir = -1;
	}
	else
	{
		*angle = 360 - *angle;
		if (*angle >= 90 && *angle <= 270)
			*dir = 1;
		else
			*dir = -1;
	}
}

float	rad(float deg)
{
	return (deg * PI / 180);
}

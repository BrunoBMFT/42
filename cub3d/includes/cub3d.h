/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 02:28:48 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define POSSIBLE "01NESW"
# define SCALE 16
# define W_STEP 0.25
# define FOV 64//use this ffs



# define WHITE 16777215
# define GREY 4210752
# define CEILING 8355711
# define FLOOR 2171169
# define GREEN 65280
# define RED 16711680

# define PI 3.14159265358979323846

//header for structs
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}				t_img;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	
	float	p_y;
	float	p_x;
	int		p_angle;
	t_img	frame;
	t_img	north;
	t_img	east;
	t_img	south;
	t_img	west;
	int		c_floor;
	int		c_ceiling;

	bool	door_opened;//bonus

	
	char		**map;
	int			map_height;
	int			map_width;
	//find better place for these
	char		**file;
	char		*p_north;
	char		*p_east;
	char		*p_south;
	char		*p_west;
	char		*p_floor;
	char		*p_ceiling;
}				t_data;


void	clear_img(t_data *data);
//parser
bool	parser(int ac, char **av, t_data *data);
bool	save_map(t_data *data);
bool	map_check(t_data *data);

//init
bool	init(int ac, char **av, t_data *data);

//minimap
void	create_map(t_data *data);

float	rad(float deg);

//test
void	raycast(t_data *data);
void	create_background(t_data *data);

//frame
void	create_frame(t_data *data);

//img
void	put_pixel(t_data *data, int y, int x, int color);

//input
int	input(int keysym, t_data *data);

//errors
bool	error(char *str);

//clean
int		clean_everything(t_data *data);
void	clean_array(char **arr);//use free_array


#endif
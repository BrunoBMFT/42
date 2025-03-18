/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2025/03/18 17:33:20 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

//header for colors
# define POSSIBLE "01NESW "
# define SCALE 50
# define WHITE 16777215
# define BLACK 8421504
# define RED 16711680
# define GREEN 65280
# define BLUE 255
# define CYAN 65535
# define PINK 16711935
# define YELLOW 16776960
# define GREY 4210752
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

typedef struct s_textures
{
	t_img *north;
	t_img *east;
	t_img *south;
	t_img *west;
}			t_textures;

typedef struct s_player
{
	float			y;
	float			x;
	float			dir_y;
	float			dir_x;
	int			color;//for minimap
	int			size;//for minimap, float?
    float		angle; // Current facing angle in radians
}				t_player;

typedef struct	s_data
{
	char		**file;
	bool		**visited;
	char		**map;
	int			max_len;

	void		*mlx;
	void		*win;
	int			mini_scale;//temp
	t_img		*minimap;//maybe have a minimap struct saving height, width and the image, optional, have the position
	int			pixel_size;
	t_img		*frame;
	t_textures	*texture;
	t_player	*player;





	//find better place for these
	char		*p_north;
	char		*p_east;
	char		*p_south;
	char		*p_west;
	char		*c_floor;
	char		*c_ceiling;
}				t_data;
void	raycast(t_data *data);

//parser
void	parser(int ac, char **av, t_data *data);
void	save_texture_path(t_data *data);
void	save_map(t_data *data);
void	flood_fill(t_data *data);

//init
void	init(t_data *data);
void	init_textures(t_data *data);

//img
int		get_pixel(t_img *img, int y, int x);
void	put_pixel(t_img *img, int y, int x, int color);
void	make_frame(t_data *data, t_img *img, int y, int x);

//minimap
void	make_minimap(t_data *data);

//remove
void 	print_map_info(t_data *data);
void 	print_file_info(t_data *data);
void	print_file(t_data *data);

//errors
void	error(t_data *data, char *str);

//clean
int		clean_everything(t_data *data);
int		close_game(t_data *data);
void	clean_array(char **arr);//use free_array

//inputs
int	handle_input(int keysym, t_data *data);


#endif
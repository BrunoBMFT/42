#ifndef STRUCTS_H
# define STRUCTS_H

// typedef struct s_coord
// {
// 	float	y;
// 	float	x;
// }				t_coord;

// typedef struct s_draw
// {
// 	float	hyp;
// 	float	angle;
// 	int		section;
// 	t_coord	coord;
// 	bool	vert;
// }			t_draw;

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

enum sprites {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	FLOOR,
	CEILING
};

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	float		p_y;
	float		p_x;
	int			p_angle;
	t_img		frame;
	//sprites
	t_img		sprites[4];
	int			color_floor;
	int			color_ceiling;
	//sprites
	int			map_active;
	char		**map;
	size_t		map_height;
	size_t		map_width;
	char		**file;
	bool		is_map;
	//paths
	bool		has_textures;
	bool		has_colors;
	char		*paths[6];
	//paths
}				t_data;

#endif
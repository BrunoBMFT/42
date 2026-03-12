#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdint.h>

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

enum key_presses {
	RIGHT_KEY,
	LEFT_KEY,
	W_KEY,
	A_KEY,
	S_KEY,
	D_KEY
};

	/*
	t_ray will have a max ray distance
		t_ray will have:
			save player x and player y
			bool hit
			the angle, calling tan just once

	*/
typedef struct	s_ray {
	double	player_x;
	double	player_y;
	double	angle;
	double	tan_a;
	bool	hit;
	double	hit_v_x;
	double	hit_v_y;
	double	hit_h_x;
	double	hit_h_y;
	double	distance_h;
	double	distance_v;
}				t_ray;

typedef struct s_data
{
	//MLX
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;

	//PLAYER
	float		p_y;
	float		p_x;
	int			p_angle;
	
	//FRAME
	t_img		frame;
	t_img		sprites[4];
	int			color_floor;
	int			color_ceiling;
	int			frame_count;
	int			start;//rename cause im not using it as start
	
	//INPUTS
	bool		inputs[6];
	int			map_active;
	bool		paused;

	//PARSING
	char		**map;
	size_t		map_height;
	size_t		map_width;
	char		**file;
	// uint8_t		is_map1;
	bool		is_map;
	bool		has_textures;
	bool		has_colors;
	char		*paths[6];

}				t_data;


#endif
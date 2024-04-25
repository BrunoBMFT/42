/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:51 by bruno             #+#    #+#             */
/*   Updated: 2024/04/26 00:29:51 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <unistd.h>
# include <stdio.h>//remove
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
# include <time.h>
# include "./libft/libft.h"
# include "messages.h"

# define VALID "01PECB"
# define SCALE 96

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

typedef struct	s_map
{
	char	**map;
	int		height;
	int		width;
	t_img 	wall;
	t_img 	floor;
	t_img 	collectible;
	t_img 	exit;
	t_img 	bomb;
	t_img 	death;
	bool	**visited;
	int		playerpos_y;
	int		playerpos_x;
	int		numplayer;
	int		numexit;
	int		numcollectible;//these 3 are for parser
}				t_map;

typedef struct s_player
{
	t_img	img;
	char	dir;
	int		x;
	int		y;
	int		input;
	int		moves;
	bool	can_exit;
	bool	is_alive;
}				t_player;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	t_map		*map;
	t_player	*player;
	t_img		*load;
	int			timer;
}				t_vars;
void	free_file(char **arr);//might not need?

//parser
bool	check_filename(char *file);
bool	read_file(t_map *map, int fd, int loop);
bool	get_file(char *file, t_map *map);
bool	parser(int ac, char **av, t_map *map);
bool	is_in_array(char *arr, char c);
bool	check_char(t_map *map);
//flood
bool	set_visited(t_map *map);
bool	initiate_flood(t_map *map);
bool	flood_fill(t_map *map, int col, int row);
bool	check_surroundings(t_map *map);
bool	validate_map(t_map *map);
//inits
bool	find_start(t_vars *vars);
bool	player_init(t_vars *vars);
bool	mlx_init_vars(t_vars *vars, t_map *map);
bool	init_img(t_vars *vars, t_img *img, int width, int height);
bool	wall_init(t_vars *vars);
bool	floor_init(t_vars *vars);
bool	collectible_init(t_vars *vars);
bool	exit_init(t_vars *vars);
bool	map_init(t_vars *vars);
//image
int	get_pixel(t_img *img, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);
void	make_img(t_img *img, t_img src, int x, int y);
void	render_map_textures(t_vars *vars, t_img *img, int x, int y);
void	render_map(t_vars *vars, t_img *img);
void	render(t_vars *vars, t_img *img);
void	render_player(t_vars *vars, t_img *img);
//moves
int	handle_move(t_vars *vars);
void	check_moves(t_vars *vars, int x, int y);
void	move_player(t_vars *vars);
int	handle_input(int keysym, t_vars *vars);
//clean
void	clean_map(t_map *map);
int		clean(t_vars *vars);
void	free_parser_map(t_map *map);

#endif

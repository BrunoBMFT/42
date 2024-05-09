/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:51 by bruno             #+#    #+#             */
/*   Updated: 2024/05/09 08:43:36 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <unistd.h>
# include <stdio.h>
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

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	t_img	wall;
	t_img	floor;
	t_img	collectible;
	t_img	bomb;
	t_img	exit;
	t_img	death;
	bool	**visited;
	int		playerpos_y;
	int		playerpos_x;
	int		numplayer;
	int		numexit;
	int		numcollectible;
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

//parser
bool	parser(int ac, char **av, t_map *map);
bool	check_filename(char *file);
bool	get_file(char *file, t_map *map);
bool	read_file(t_map *map, int fd, int loop);
bool	validate_map(t_map *map);
bool	check_char(t_map *map);
bool	is_in_array(char *arr, char c);
//flood
bool	initiate_flood(t_map *map);
bool	set_visited(t_map *map);
bool	check_surroundings(t_map *map);
bool	flood_fill(t_map *map, int col, int row);
//inits
bool	mlx_init_vars(t_vars *vars, t_map *map);
bool	init_img(t_vars *vars, t_img *img, int width, int height);
bool	player_init(t_vars *vars);
bool	find_start(t_vars *vars);
bool	map_init(t_vars *vars);
//textures
bool	wall_init(t_vars *vars);
bool	floor_init(t_vars *vars);
bool	collectible_init(t_vars *vars);
bool	bomb_init(t_vars *vars);
bool	exit_init(t_vars *vars);
bool	death_init(t_vars *vars);
//render
void	render(t_vars *vars, t_img *img);
void	render_map(t_vars *vars, t_img *img);
void	render_map_textures(t_vars *vars, t_img *img, int x, int y);
void	render_player(t_vars *vars, t_img *img);
void	make_img(t_img *img, t_img src, int x, int y);
int		get_pixel(t_img *img, int x, int y);
void	put_pixel(t_img *img, int x, int y, int color);
//moves
int		handle_move(t_vars *vars);
int		handle_input(int keysym, t_vars *vars);
void	move_player(t_vars *vars);
void	check_moves(t_vars *vars, int x, int y);
//clean
int		clean(t_vars *vars);
void	clean_map(t_map *map);
void	free_file(char **arr);
void	free_parser_map(t_map *map);

#endif

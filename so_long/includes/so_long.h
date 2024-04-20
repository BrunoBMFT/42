/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:51 by bruno             #+#    #+#             */
/*   Updated: 2024/04/20 19:00:37 by bruno            ###   ########.fr       */
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
# include "./libft/libft.h"
# include "messages.h"

# define VALID "01PEC"
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
	/*t_img 	wall_north;
	t_img 	wall_north_east;
	t_img 	wall_east;
	t_img 	wall_north_west;
	t_img 	wall_west;*/
	t_img 	wall;
	t_img 	floor;
	bool	**visited;
	int		row;
	int		col;
}				t_map;

typedef struct s_player
{
	t_img	img;
	char	dir;//N, E, S, W
	int		x;
	int		y;
	int		input;
	//moves, next, prev (next is to calculate next move)
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
}				t_vars;

bool	parser(int ac, char **av, t_map *map);


//inits
/*void	wall_north_init(t_vars *vars);
void	wall_north_east_init(t_vars *vars);
void	wall_east_init(t_vars *vars);
void	wall_north_west_init(t_vars *vars);
void	wall_west_init(t_vars *vars);
void	wall_CENTER_init(t_vars *vars);*/
void	wall_init(t_vars *vars);
void	floor_init(t_vars *vars);


//inputs
int	handle_input(int keysym, t_vars *vars);

//clean
void	freemap(t_map *map);//make my own
int	clean(t_vars *vars);//make my own

//image
void	make_img(t_img *img, t_img src, int x, int y);

//player
bool	player_init(t_vars *vars);
void	render_player(t_vars *vars, t_img *img);
int		handle_move(t_vars *vars);

#endif

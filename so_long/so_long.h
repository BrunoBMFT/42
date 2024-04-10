/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:51 by bruno             #+#    #+#             */
/*   Updated: 2024/04/10 19:34:56 by brfernan         ###   ########.fr       */
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

typedef struct s_img
{
	void	*img;
	char	*address;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
	int		width;
	int		height;
}				t_img;

typedef struct	s_map
{
	char	**map;
	bool	**visited;
	int		col;
	int		row;
	t_img 	wall;
}				t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	t_map	*map;
}				t_vars;

bool	parser(int ac, char **av, t_map *map);
void	free_file(char **arr);
void	init(t_map *map);
void	free_parser(t_map *map);
void	map_init(t_map *map);

#endif
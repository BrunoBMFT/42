/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 04:57:39 by brfernan          #+#    #+#             */
/*   Updated: 2025/05/03 16:23:45 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_coord
{
	float	y;
	float	x;
}				t_coord;

typedef struct s_draw
{
	float	hyp;
	float	angle;
	int		section;
	t_coord	coord;
	bool	vert;
}			t_draw;

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
	t_img		north;
	t_img		east;
	t_img		south;
	t_img		west;
	int			color_floor;
	int			color_ceiling;
	int			door_opened;//bonus
	int			map_active;//bonus
	char		**map;
	size_t		map_height;
	size_t		map_width;
	char		**file;
	char		*path_north;
	char		*path_east;
	char		*path_south;
	char		*path_west;
	char		*path_floor;
	char		*path_ceiling;
}				t_data;

#endif
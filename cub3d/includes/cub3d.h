/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2025/04/07 20:18:15 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "structs.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define POSSIBLE "01NESWD"
# define SCALE 16
# define W_STEP 0.25
# define A_STEP 10
# define FOV 64
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define WHITE 16777215
# define GREY 4210752
# define GREEN 65280
# define RED 16711680
# define PI 3.14159265358979323846

//init
bool	init(int ac, char **av, t_data *data);
bool	parser(int ac, char **av, t_data *data);
bool	save_map(t_data *data);
bool	map_check(t_data *data);
bool	save_texture_path(t_data *data);
bool	texture_check(t_data *data);
bool	init_imgs(t_data *data);
bool	player_init(t_data *data);

//raycast
void	raycast(t_data *data);
void	draw_wall_section(t_data *data, t_draw *info);
void	create_background(t_data *data);
void	angle_correct(float *angle, int *dir, bool is_h);
float	rad(float deg);

//utils
bool	is_allowed(char *str);
void	create_frame(t_data *data);
void	create_map(t_data *data);
void	put_pixel(t_data *data, int y, int x, int color);
int     get_pixel(t_img *img, int x, int y);
void	clear_img(t_data *data);
int		input(int keysym, t_data *data);
bool	error(char *str);
int		clean_everything(t_data *data);
int		clean_exit(t_data *data);

#endif
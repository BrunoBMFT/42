/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2025/03/07 19:37:55 by bruno            ###   ########.fr       */
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

//header for structs

typedef struct	s_data
{
	char		**file;
	char		**map;
	//find better place for these
	char		*p_north;
	char		*p_east;
	char		*p_south;
	char		*p_west;
	char		*c_floor;
	char		*c_ceiling;
}				t_data;

//parser
bool	parser(int ac, char **av, t_data *data);
bool	save_map(t_data *data);

//errors
bool	error(char *str);

//clean
int		clean_everything(t_data *data);
void	clean_array(char **arr);//use free_array


#endif
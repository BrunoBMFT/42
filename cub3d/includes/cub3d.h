/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2024/12/14 12:57:10 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"

# define POSSIBLE "01NESW "

typedef struct	s_data
{
	char		**file;
	bool		**visited;
	int			y_start;
	int			x_start;
	int			starts;
	char		**map;
	char		*p_north;
	char		*p_east;
	char		*p_south;
	char		*p_west;
	char		*c_floor;
	char		*c_ceiling;
}				t_data;

//parser
void	parser(int ac, char **av, t_data *data);
void	save_texture_path(t_data *data);
void	save_map(t_data *data);
void	flood_fill(t_data *data);

//remove
void 	print_map_info(t_data *data);
void 	print_file_info(t_data *data);
void	print_file(t_data *data);

//errors
void	error(t_data *data, char *str);

//clean
void	clean_everything(t_data *data);
void	clean_file(t_data *data);
void	clean_array(char **arr);//put in libft



#endif
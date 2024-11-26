/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 00:43:02 by bruno             #+#    #+#             */
/*   Updated: 2024/11/26 01:49:26 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"


typedef struct	s_data
{
	char	**file;
	char	*tnorth;//have array of strings for textures
	char	*tsouth;
	char	*teast;
	char	*twest;
	char	**map;
}				t_data;

//parser
void	name_check(int ac, char **av);
void	save_map(t_data *data, char *str);
//remove
void 	print_map_info(t_data *data);
void 	print_file_info(t_data *data);

//errors
void	error(char *str);

//clean
void	clean_map(t_data *data);



#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:20:51 by bruno             #+#    #+#             */
/*   Updated: 2024/09/27 18:57:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUDOKU_H
# define SUDOKU_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <fcntl.h>
# include <time.h>
# include "./libft/libft.h"
# include "messages.h"
# include <string.h>

# define VALID "0123456789-| +"
# define SCALE 96


typedef struct s_map
{
	char	**map;
	char	**img;
	char	**rows;
	char	**cols;
	char	**small_grids;
	int		*start;
	bool	solved;
}				t_map;


bool	parser(int ac, char **av, t_map *map);
void	solve(t_map *map);
void 	init_map(t_map *map);
void	init_grid(t_map *map);
void	print_map(t_map *map);
void	update_map(t_map *map);


#endif

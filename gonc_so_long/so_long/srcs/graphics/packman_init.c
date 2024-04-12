/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pacman_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:20:18 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:16:33 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	pacman_init(t_data *vars)
{
	vars->pacman = malloc(sizeof(t_pacman));
	if (vars->pacman == NULL)
		error_message("Error\nMalloc failed\n");
	find_start(vars);
	vars->pacman->dir = 's';
	vars->pacman->next = 's';
	vars->pacman->prev = 's';
	vars->pacman->moves = 0;
	vars->pacman->img[0].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_0.xpm", &vars->pacman->img[0].width,
			&vars->pacman->img[0].height);
	get_addr(vars);
}

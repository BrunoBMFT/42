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
	pacman_init2(vars);
	pacman_init3(vars);
	get_addr(vars);
}

void	pacman_init2(t_data *vars)
{
	vars->pacman->img[0].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_0.xpm", &vars->pacman->img[0].width,
			&vars->pacman->img[0].height);
	vars->pacman->img[1].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_1.xpm", &vars->pacman->img[1].width,
			&vars->pacman->img[1].height);
	vars->pacman->img[2].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_2.xpm", &vars->pacman->img[2].width,
			&vars->pacman->img[2].height);
	vars->pacman->img[3].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_3.xpm", &vars->pacman->img[3].width,
			&vars->pacman->img[3].height);
	vars->pacman->img[4].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_4.xpm", &vars->pacman->img[4].width,
			&vars->pacman->img[4].height);
	vars->pacman->img[5].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_5.xpm", &vars->pacman->img[5].width,
			&vars->pacman->img[5].height);
	vars->pacman->img[6].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_6.xpm", &vars->pacman->img[6].width,
			&vars->pacman->img[6].height);
	vars->pacman->img[7].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_7.xpm", &vars->pacman->img[7].width,
			&vars->pacman->img[7].height);
}

void	pacman_init3(t_data *vars)
{
	vars->pacman->img[8].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_8.xpm", &vars->pacman->img[8].width,
			&vars->pacman->img[8].height);
	vars->pacman->img[9].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_9.xpm", &vars->pacman->img[9].width,
			&vars->pacman->img[9].height);
	vars->pacman->img[10].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_10.xpm", &vars->pacman->img[10].width,
			&vars->pacman->img[10].height);
	vars->pacman->img[11].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_11.xpm", &vars->pacman->img[11].width,
			&vars->pacman->img[11].height);
	vars->pacman->img[12].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_12.xpm", &vars->pacman->img[12].width,
			&vars->pacman->img[12].height);
	vars->pacman->img[13].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_13.xpm", &vars->pacman->img[13].width,
			&vars->pacman->img[13].height);
	vars->pacman->img[14].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_14.xpm", &vars->pacman->img[14].width,
			&vars->pacman->img[14].height);
	vars->pacman->img[15].img = mlx_xpm_file_to_image(vars->mlx,
			"./includes/textures/pacman_15.xpm", &vars->pacman->img[15].width,
			&vars->pacman->img[15].height);
}

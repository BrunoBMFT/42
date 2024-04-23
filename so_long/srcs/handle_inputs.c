/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:34:50 by bruno             #+#    #+#             */
/*   Updated: 2024/04/23 19:09:12 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render(t_vars *vars, t_img *img)
{
	render_map(vars, img);
	make_img(img, vars->player->img, vars->player->x, vars->player->y);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

void	random_move(t_vars *vars)
{
	time_t t;
	srand((unsigned) time(&t));
	printf("%d", rand() % 4);
	vars->timer++;
//	if (vars->timer >= 60)
//	printf("%d\n", vars->timer);
	if (vars->timer >= 150)
		vars->timer = 0;
}

int	handle_move(t_vars *vars)//might not need?
{
	random_move(vars);
	render(vars, vars->load);
	return (1);
}

void	check_moves(t_vars *vars, int x, int y)
{
	if (vars->player->x != x || vars->player->y != y)
		ft_printf("%d\n", vars->player->moves++);
	if (vars->map->map[vars->player->y / SCALE][vars->player->x / SCALE] == 'C')
		vars->player->can_exit = true;
	if (vars->player->can_exit && vars->map->map[vars->player->y / SCALE]
		[vars->player->x / SCALE] == 'E')
		return (clean(vars), exit(1));
}

void	move_player(t_vars *vars)
{
	int	x;
	int	y;

	y = vars->player->y;
	x = vars->player->x;
	if (vars->player->input == 'N' && vars->map->map[vars->player->y
			/ SCALE - 1][vars->player->x / SCALE] != '1')
		vars->player->y -= 1 * SCALE;
	if (vars->player->input == 'S' && vars->map->map[vars->player->y
			/ SCALE + 1][vars->player->x / SCALE] != '1')
		vars->player->y += 1 * SCALE;
	if (vars->player->input == 'E' && vars->map->map[vars->player->y / SCALE]
		[vars->player->x / SCALE + 1] != '1')
		vars->player->x += 1 * SCALE;
	if (vars->player->input == 'W' && vars->map->map[vars->player->y / SCALE]
		[vars->player->x / SCALE - 1] != '1')
		vars->player->x -= 1 * SCALE;
	check_moves(vars, x, y);
}

int	handle_input(int keysym, t_vars *vars)
{
	if (keysym == XK_Escape)
		clean(vars);
	if (keysym == 'w' || keysym == XK_Up)
		vars->player->input = 'N';
	if (keysym == 'd' || keysym == XK_Right)
		vars->player->input = 'E';
	if (keysym == 's' || keysym == XK_Down)
		vars->player->input = 'S';
	if (keysym == 'a' || keysym == XK_Left)
		vars->player->input = 'W';
	move_player(vars);
	return (0);
}

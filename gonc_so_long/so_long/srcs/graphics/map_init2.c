/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfernan <brfernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:13:24 by gfontao-          #+#    #+#             */
/*   Updated: 2024/04/12 16:19:31 by brfernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long_bonus.h"

void	map_init(t_data *vars)
{
	wall_init(vars);
	floor_init(vars);
	exit_init(vars);
	collectible_init(vars);
	border_init(vars);
}

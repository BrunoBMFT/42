/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:33:44 by bruno             #+#    #+#             */
/*   Updated: 2024/12/15 13:34:08 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_data *data)
{
	clean_everything(data);
	exit (0);
	return (0);//for -wall -werror -wextra
}

int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		close_game(data);
	return (0);
}
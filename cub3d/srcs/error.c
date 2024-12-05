/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:12:04 by bruno             #+#    #+#             */
/*   Updated: 2024/12/03 19:22:03 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(t_data *data, char *str)//have this call the frees function
{
	// clean_everything(data);
	ft_printf_fd(2, "Error!\n%s\n", str);
	exit (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 23:55:16 by bruno             #+#    #+#             */
/*   Updated: 2024/07/11 03:36:27 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_free_array(char **array)
{
    int i;

    i = 0;
    if (!array || !array[i])
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}
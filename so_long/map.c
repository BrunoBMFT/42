/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:45:17 by bruno             #+#    #+#             */
/*   Updated: 2024/04/01 17:28:05 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	int	fd;
	char *ret;
	fd = open("/home/bruno/42/so_long/test.ber", O_RDONLY);
	if (fd == -1)
	{
		perror("Error in opening file");
		return (1);
	}
	ret = get_next_line(fd);
	while (ret)
	{
		printf("%s", ret);
		free(ret);
		ret = get_next_line(fd);
	}
	close(fd);
}

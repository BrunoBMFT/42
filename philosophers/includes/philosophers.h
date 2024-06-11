/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 01:49:43 by bruno             #+#    #+#             */
/*   Updated: 2024/06/11 02:15:02 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define WRONGARGS "wrong type of argument"
# define BIGINT "bigger than intmax"
# define NOPHILO "not enough philosophers"

bool	parser(int ac, char **av);

#endif
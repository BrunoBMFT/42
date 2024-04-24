/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:52:23 by bruno             #+#    #+#             */
/*   Updated: 2024/04/23 23:50:09 by bruno            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGES_H
# define MESSAGES_H

//parser
# define INV_MAPNAME "Error\nInvalid map name"
# define INV_ARGS "Error\nInvalid number of arguments"
# define INV_FILE "Error\nFile not found"
# define ERR_FILE "Error\nCouldn't read file"
# define INV_MAP "Error\nInvalid map"
# define ERR_ALLOC "Error\nFailed allocating memory"
# define INV_CHAR "Error\nInvalid char in map"
# define ERR_MAP "Error\nFailed validating map"
# define INV_PLAYEREXITCOLL "Error\nInvalid player, exit or collectible count"

//inits
# define ERR_WIN "Error\nFailed creating window"
# define ERR_MLX "Error\nFailed initiating mlx"
# define ERR_IMG "Error\nFailed initiating image"
//textures
# define INV_WALL "Error\nInvalid wall"
# define INV_FLOOR "Error\nInvalid floor"
# define INV_COLLECTIBLE "Error\nInvalid collectible"
# define INV_EXIT "Error\nInvalid exit"
# define INV_BOMB "Error\nInvalid bomb"
# define INV_DEATH "Error\nInvalid death"

//player
# define ERR_ALLOC_PLAYER "Error\nFailed allocating player memory"
# define INV_PLAYER "Error\nInvalid player"
# define INV_PLAYERPOS "Error\nInvalid player"

#endif
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strcat.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: brfernan <brfernan@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/06/26 18:01:46 by brfernan		   #+#	#+#			 */
/*   Updated: 2024/06/26 18:03:07 by brfernan		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_strcat(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

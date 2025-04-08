/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:10:09 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:33:47 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (x < len && big[x] != '\0')
	{
		if (big[x] == little[y])
		{
			while (big[x + y] == little[y] && (x + y) < len)
			{
				if (little[y + 1] == '\0')
					return ((char *)big + x);
				y++;
			}
			y = 0;
		}
		x++;
	}
	return (NULL);
}

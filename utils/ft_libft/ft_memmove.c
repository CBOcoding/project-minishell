/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:21 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 14:03:54 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*source;
	unsigned char		*destination;

	i = 0;
	source = (const unsigned char *)src;
	destination = (unsigned char *)dst;
	if (source < destination)
	{
		while (n > 0)
		{
			n--;
			destination[n] = source[n];
		}
	}
	else if (source > destination)
	{
		while (i < n)
		{
			destination[i] = source[i];
			i++;
		}
	}
	return (destination);
}

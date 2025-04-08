/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:03 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:32:54 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size == 0)
	{
		while (src[x] != '\0')
			x++;
		return (x);
	}
	while (src[x] != '\0' && x < (size - 1))
	{
		dst[x] = src[x];
		x++;
	}
	if (x < size)
		dst[x] = '\0';
	return (ft_strlen(src));
}

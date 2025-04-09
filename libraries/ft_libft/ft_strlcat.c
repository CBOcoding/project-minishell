/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:07 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/08 11:58:21 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if ((dst == NULL || src == NULL) && !size)
		return (0);
	while (dst[x] != '\0' && x < size)
	{
		x++;
	}
	while (src[y] != '\0' && (x + y + 1) < size)
	{
		dst[x + y] = src[y];
		y++;
	}
	if (x < size)
	{
		dst[x + y] = '\0';
	}
	return (x + ft_strlen(src));
}

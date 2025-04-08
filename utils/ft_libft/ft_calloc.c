/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:43:53 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:11:31 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	char	*pointer;
	size_t	x;

	if (count == 0 || size == 0)
		return (malloc(1));
	total_size = count * size;
	pointer = (void *)malloc(total_size);
	x = 0;
	if (pointer == NULL)
		return (NULL);
	while (x < total_size)
	{
		pointer[x] = 0;
		x++;
	}
	return (pointer);
}

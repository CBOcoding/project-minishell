/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:36 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:17:44 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*area1;

	i = 0;
	area1 = (char *)s;
	while (i < n)
	{
		if ((unsigned char) area1[i] == (unsigned char) c)
			return (&area1[i]);
		i++;
	}
	return (NULL);
}

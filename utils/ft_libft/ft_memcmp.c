/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:31 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:18:09 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*area1;
	char	*area2;
	size_t	i;

	area1 = (char *)s1;
	area2 = (char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (area1[i] == area2[i])
			i++;
		else
			return ((unsigned char) area1[i] - (unsigned char) area2[i]);
	}
	return (0);
}

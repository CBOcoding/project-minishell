/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:57:05 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 10:27:33 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	x;
	size_t	y;

	trimmed = 0;
	x = 0;
	y = ft_strlen(s1);
	if (s1 != 0 && set != 0)
	{
		while (s1[x] != '\0' && ft_strchr(set, s1[x]))
		{
			x++;
		}
		while (s1[y - 1] && ft_strchr(set, s1[y - 1]) && y > x)
		{
			y--;
		}
		trimmed = (char *)malloc((y - x + 1) * sizeof(char));
		if (trimmed == NULL)
			return (NULL);
		else
			ft_strlcpy(trimmed, &s1[x], y - x + 1);
	}
	return (trimmed);
}

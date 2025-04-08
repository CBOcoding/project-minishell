/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:19:39 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:31:16 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	x;
	size_t	y;

	substring = (char *) malloc ((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s[x] != '\0')
	{
		if (x >= start && y < len)
		{
			substring[y] = s[x];
			y++;
		}
		x++;
	}
	substring[y] = '\0';
	return (substring);
}

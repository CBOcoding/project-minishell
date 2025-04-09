/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:02:41 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 10:25:51 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	size_t	lens1s2;
	char	*newstring;

	lens1s2 = ft_strlen(s1) + ft_strlen(s2);
	newstring = (char *)malloc((lens1s2 + 1) * sizeof(char));
	if (newstring == NULL)
		return (NULL);
	x = 0;
	y = 0;
	while (s1[x])
	{
		newstring[x + y] = s1[x];
		x++;
	}
	while (s2[y])
	{
		newstring[x + y] = s2[y];
		y++;
	}
	newstring[x + y] = '\0';
	return (newstring);
}

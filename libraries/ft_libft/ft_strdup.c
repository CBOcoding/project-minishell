/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 08:44:24 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/07 11:21:35 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*src;
	char	*scopy;
	int		x;

	src = (char *)s;
	scopy = (char *) malloc((ft_strlen(src) + 1) * sizeof(char));
	if (scopy == NULL)
		return (NULL);
	x = 0;
	while (src[x] != '\0')
	{
		scopy[x] = src[x];
		x++;
	}
	scopy[x] = '\0';
	return (scopy);
}

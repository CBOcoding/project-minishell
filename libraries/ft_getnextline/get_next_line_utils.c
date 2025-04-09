/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:09:37 by cborrome          #+#    #+#             */
/*   Updated: 2024/11/28 12:20:28 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char *s)
{
	size_t		i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_prepare_str1(char *str1)
{
	if (!str1)
	{
		str1 = (char *)malloc(sizeof(char) * 1);
		if (str1 == NULL)
			return (NULL);
		str1[0] = '\0';
	}
	return (str1);
}

char	*ft_strjoin_gnl(char *str1, char *buffer)
{
	size_t		i;
	size_t		j;
	char		*output;

	str1 = ft_prepare_str1(str1);
	if (str1 == NULL || buffer == NULL)
		return (NULL);
	output = (char *)malloc(sizeof(char) * \
	(ft_strlen_gnl(str1) + ft_strlen_gnl(buffer) + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
		output[j++] = str1[i++];
	i = 0;
	while (buffer[i])
		output[j++] = buffer[i++];
	output[j] = '\0';
	free(str1);
	return (output);
}

char	*ft_strchr_gnl(char *string, int c)
{
	size_t	i;

	i = 0;
	if (string == NULL)
		return (0);
	if (c == '\0')
		return (&string[ft_strlen_gnl(string)]);
	while (string[i] != '\0')
	{
		if (string[i] == (char) c)
			return (&string[i]);
		i++;
	}
	return (0);
}

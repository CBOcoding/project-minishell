/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:41:33 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:41:33 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_closed_quotes(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i])
			{
				if (str[i] == quote)
					return (SUCCESS);
				i++;
			}
		}
		i++;
	}
	return (FAILURE);
}

int	ft_strcmp(const char *main, const char *compared)
{
	int	i;

	i = 0;
	while (compared[i] || main[i])
	{
		if (compared[i] != main[i])
			return (main[i] - compared[i]);
		i++;
	}
	return (SUCCESS);
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	is_cmd(char c)
{
	return (c == '>' || c == '<'
		|| c == '|' || c == '\''
		|| c == '"');
}

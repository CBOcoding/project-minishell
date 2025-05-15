/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:14 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:14 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_newline_option(int *newline, int *i, t_token **token)
{
	*newline = 0;
	(*i)++;
	*token = (*token)->next;
	*token = (*token)->next;
}

static void	handle_add_space(t_token *token)
{
	if (!token->skip_space)
		ft_putstr_fd(" ", 1);
	else if (token->skip_space > 0)
		token->skip_space--;
}

int	builtin_echo(char **argv, t_token *token)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!token)
		return (SUCCESS);
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		handle_no_newline_option(&newline, &i, &token);
	else
		token = token->next;
	while (argv[i] && token)
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			handle_add_space(token);
		i++;
		token = token->next;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (SUCCESS);
}

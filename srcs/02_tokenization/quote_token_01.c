/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:41:37 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:41:37 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokenize_word_dquote(char *input, int start, int *i, t_token **tok)
{
	char	*word;
	t_token	*new_token;

	if (*i > start)
	{
		word = ft_substr(input, start, *i - start);
		if (word && *word)
		{
			new_token = create_token(word, WORD);
			new_token->status = DQUOTE;
			add_token(tok, new_token);
		}
		free(word);
	}
}

void	handle_dquote_dollar(char *input, int *i, int *start, t_token **tok)
{
	tokenize_word_dquote(input, *start, i, tok);
	tokenize_var_in_dquote(input, i, tok);
	*start = *i;
}

void	tokenize_dquote(char *input, int *i, t_token **tok, t_status *status)
{
	int	start;

	if (input[*i + 1] == '"')
	{
		(*i) += 2;
		*status = DEFAULT;
		return ;
	}
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			handle_dquote_dollar(input, i, &start, tok);
			continue ;
		}
		(*i)++;
	}
	tokenize_word_dquote(input, start, i, tok);
	if (input[*i] == '"')
	{
		(*i)++;
		*status = DEFAULT;
	}
}

static void	create_delim_token(char *input, int start, int *i, t_token **delim)
{
	char	*content;

	content = ft_substr(input, start + 1, *i - start - 2);
	*delim = create_token(content, WORD);
	free(content);
}

void	empty_quote_handler(char *input, int *i, t_token **delim)
{
	int		start;

	start = *i;
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != '\'')
			(*i)++;
		if (input[*i] == '\'')
			(*i)++;
		create_delim_token(input, start, i, delim);
	}
	else if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] && input[*i] != '"')
			(*i)++;
		if (input[*i] == '"')
			(*i)++;
		create_delim_token(input, start, i, delim);
	}
}

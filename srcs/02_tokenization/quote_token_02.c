/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:41:39 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/16 14:55:08 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_squote_token(char *input, int start, int *i, t_token **tok)
{
	char	*word;
	t_token	*new_token;

	word = ft_substr(input, start, *i - start);
	if (word && *word)
	{
		new_token = create_token(word, WORD);
		new_token->status = SQUOTE;
		add_token(tok, new_token);
	}
	free(word);
}

void	handle_dquote_dollar(char *input, int *i, int *start, t_token **tok)
{
	tokenize_word_dquote(input, *start, i, tok);
	tokenize_var_in_dquote(input, i, tok);
	*start = *i;
}

void	check_token_spacing(char *input, int i, t_token **tok)
{
	t_token	*last;

	if (input[i] && !ft_isspace(input[i]) && !is_cmd(input[i]))
	{
		last = *tok;
		while (last && last->next)
			last = last->next;
		if (last)
			last->skip_space = 1;
	}
}

void	tokenize_squote(char *input, int *i, t_token **tok, t_status *status)
{
	int		start;

	if (input[*i + 1] == '\'')
	{
		(*i) += 2;
		*status = DEFAULT;
		check_token_spacing(input, *i, tok);
		return ;
	}
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	handle_squote_token(input, start, i, tok);
	if (input[*i] == '\'')
	{
		(*i)++;
		*status = DEFAULT;
		check_token_spacing(input, *i, tok);
	}
}

void	tokenize_var_in_dquote(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*var_name;
	t_token	*new_token;

	start = *i;
	(*i)++;
	if (input[*i] == '?')
	{
		var_name = ft_strdup("$?");
		(*i)++;
	}
	else
	{
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		var_name = ft_substr(input, start, *i - start);
	}
	if (var_name && *var_name)
	{
		new_token = create_token(var_name, ENV_VAR);
		new_token->status = DQUOTE;
		add_token(tokens, new_token);
		free(var_name);
	}
}

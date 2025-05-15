#include "minishell.h"

static void	handle_normal_delimiter(char *input, int *i, t_token **delim)
{
	int		start;
	char	*content;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_cmd(input[*i]))
		(*i)++;
	content = ft_substr(input, start, *i - start);
	*delim = create_token(content, WORD);
	free(content);
}

void	handle_delimiter(char *input, int *i, t_token *delim, t_token **tok)
{
	while (input[*i] && ft_isspace(input[*i]))
		(*i)++;
	if (input[*i] == '\'' || input[*i] == '"')
		empty_quote_handler(input, i, &delim);
	else
		handle_normal_delimiter(input, i, &delim);
	delim->status = SQUOTE;
	add_token(tok, delim);
}

void	token_status(char *input, int *i, t_token **tokens, t_status *status)
{
	if (input[*i] == '\'')
	{
		*status = SQUOTE;
		tokenize_squote(input, i, tokens, status);
	}
	else if (input[*i] == '"')
	{
		*status = DQUOTE;
		tokenize_dquote(input, i, tokens, status);
	}
	else if (input[*i] == '$')
		tokenize_var(input, i, tokens);
	else
		tokenize_simple_word(input, i, tokens);
}

void	handle_status(char *input, int *i, t_token **tokens, t_status *status)
{
	t_token	*last;
	t_token	*current;

	last = NULL;
	current = *tokens;
	while (current && current->next)
		current = current->next;
	if (current)
		last = current;
	if (input[*i] == '$' && *i > 0 && !ft_isspace(input[*i - 1]))
	{
		tokenize_var(input, i, tokens);
		return ;
	}
	if (*status == DEFAULT)
	{
		if ((input[*i] == '\'' || input[*i] == '"')
			&& *i > 0 && !ft_isspace(input[*i - 1]) && last)
			last->skip_space = 1;
		token_status(input, i, tokens, status);
	}
	else if (*status == SQUOTE)
		tokenize_squote(input, i, tokens, status);
	else if (*status == DQUOTE)
		tokenize_dquote(input, i, tokens, status);
}

void	tokenize_word(char *input, int *i, t_token **tokens, t_status *status)
{
	t_token	*prev;
	t_token	*current;
	t_token	*delim_token;
	int		quote_follows;

	prev = NULL;
	current = *tokens;
	delim_token = NULL;
	quote_follows = 0;
	while (current && current->next)
		current = current->next;
	if (current && current->type == HEREDOC)
		prev = current;
	if (*status == DEFAULT
		&& (input[*i] == '\'' || input[*i] == '"')
		&& *i > 0 && !ft_isspace(input[*i - 1]))
		quote_follows = 1;
	if (prev && prev->type == HEREDOC && *status == DEFAULT)
		handle_delimiter(input, i, delim_token, tokens);
	else
	{
		handle_status(input, i, tokens, status);
		if (quote_follows && current && current != *tokens)
			current->skip_space = 1;
	}
}

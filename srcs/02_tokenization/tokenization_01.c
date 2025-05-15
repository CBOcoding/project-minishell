#include "minishell.h"

static void	handle_status(char *input, int *i, t_token **tokens, \
							t_status *status)
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
		if ((input[*i] == '\'' || input[*i] == '"') && *i > 0 \
				&& !ft_isspace(input[*i - 1]) && last)
		{
			last->skip_space = 1;
		}
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
	else if (*status == SQUOTE)
		tokenize_squote(input, i, tokens, status);
	else if (*status == DQUOTE)
		tokenize_dquote(input, i, tokens, status);
}

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

void	tokenize_word(char *input, int *i, t_token **tokens, t_status *status)
{
	t_token	*prev;
	t_token	*current;
	t_token	*delim_token;
	int		quote_follows;

	prev = NULL;
	current = *tokens;
	quote_follows = 0;
	while (current && current->next)
		current = current->next;
	if (current && current->type == HEREDOC)
		prev = current;
	if (*status == DEFAULT && (input[*i] == '\'' || input[*i] == '"') && *i > 0 \
			&& !ft_isspace(input[*i - 1]))
	{
		quote_follows = 1;
	}
	if (prev && prev->type == HEREDOC && *status == DEFAULT)
	{
		while (input[*i] && ft_isspace(input[*i]))
			(*i)++;
		if (input[*i] == '\'' || input[*i] == '"')
			empty_quote_handler(input, i, &delim_token);
		else
			handle_normal_delimiter(input, i, &delim_token);
		delim_token->status = SQUOTE;
		add_token(tokens, delim_token);
	}
	else
	{
		handle_status(input, i, tokens, status);
		if (quote_follows && current && current != *tokens)
		{
			current->skip_space = 1;
		}
	}
}

static void	unclosed_quotes_handle(t_status status, t_token **tokens)
{
	if (status != DEFAULT)
	{
		ft_putstr_fd("Error: Unclosed quotes\n", 2);
		free_token(*tokens);
		*tokens = NULL;
	}
}

t_token	*tokenize_input(char *input)
{
	t_token		*tokens;
	t_status	status;
	int			i;

	tokens = NULL;
	status = DEFAULT;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]) && status == DEFAULT)
			i++;
		if (status == DEFAULT)
			if (tokenize_options(input, &i, &tokens) == SUCCESS)
				continue ;
		tokenize_word(input, &i, &tokens, &status);
	}
	unclosed_quotes_handle(status, &tokens);
	return (tokens);
}

#include"minishell.h"

void	tokenize_squote(char *input, int *i, t_token **tok, t_status *status)
{
	int		start;
	char	*word;
	t_token	*new_token;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	word = ft_substr(input, start, *i - start);
	if (word && *word)
	{
		new_token = create_token(word, WORD);
		new_token->status = SQUOTE;
		add_token(tok, new_token);
		free(word);
	}
	if (input[*i] == '\'')
	{
		(*i)++;
		*status = DEFAULT;
	}
}

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

void	tokenize_dquote(char *input, int *i, t_token **tok, t_status *status)
{
	int	start;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
		{
			tokenize_word_dquote(input, start, i, tok);
			tokenize_var_in_dquote(input, i, tok);
			start = *i;
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

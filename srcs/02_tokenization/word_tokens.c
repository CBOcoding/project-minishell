#include "minishell.h"
// Handle single quoted text
void	tokenize_squote(char *input, int *i, t_token **tok, t_status *status)
{
	int		start;
	char	*word;
	t_token	*new_token;

	(*i)++; // Skip opening quote
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
		(*i)++; // Skip closing quote
		*status = DEFAULT;
	}
}
// Handle double quoted text
void	tokenize_dquote(char *input, int *i, t_token **tok, t_status *status)
{
	int		start;
	char	*word;
	t_token	*new_token;

	(*i)++; // Skip opening quote
	start = *i;
	while (input[*i] && input[*i] != '"')
	{
		// Handle variable inside double quotes
		if (input[*i] == '$')
		{
			// Add content before the variable
			if (*i > start)
			{
				word = ft_substr(input, start, *i - start);
				if (word && *word)
				{
					new_token = create_token(word, WORD);
					new_token->status = DQUOTE;
					add_token(tok, new_token);
					free(word);
				}
			}
			tokenize_var_in_dquote(input, i, tok);
			start = *i;
			continue;
		}
		(*i)++;
	}
	// Add remaining content in quotes
	if (*i > start)
	{
		word = ft_substr(input, start, *i - start);
		if (word && *word)
		{
			new_token = create_token(word, WORD);
			new_token->status = DQUOTE;
			add_token(tok, new_token);
			free(word);
		}
	}
	if (input[*i] == '"')
	{
		(*i)++; // Skip closing quote
		*status = DEFAULT;
	}
}

// Handle regular word (not in quotes)
void	tokenize_simple_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	t_token	*new_token;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i])
		&& input[*i] != '>' && input[*i] != '<'
		&& input[*i] != '|' && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '$')
			(*i)++;
	word = ft_substr(input, start, *i - start);
	if (word && *word)
	{
		new_token = create_token(word, WORD);
		new_token->status = DEFAULT;
		add_token(tokens, new_token);
		free(word);
	}
}

// Handle environment variable in double quotes
void	tokenize_var_in_dquote(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*var_name;
	t_token	*new_token;

	start = *i;
	(*i)++; // Skip '$'
	// Handle special case of $?
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
// Update the existing tokenize_var function to handle variables outside quotes
void	tokenize_var(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*var_name;
	t_token	*new_token;

	start = *i;
	// Handle special case of $?
	if (input[*i + 1] == '?')
	{
		var_name = ft_strdup("$?");
		(*i) += 2;
	}
	else
	{
		(*i)++; // Skip '$'
		while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
			(*i)++;
		var_name = ft_substr(input, start, *i - start);
	}
	if (var_name && *var_name)
	{
		new_token = create_token(var_name, ENV_VAR);
		new_token->status = DEFAULT;
		add_token(tokens, new_token);
		free(var_name);
	}
}

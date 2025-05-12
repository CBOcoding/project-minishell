#include "minishell.h"

void	tokenize_simple_word(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	t_token	*new_token;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) \
	&& input[*i] != '>' && input[*i] != '<' \
	&& input[*i] != '|' && input[*i] != '\'' \
	&& input[*i] != '"' && input[*i] != '$')
		(*i)++;
	word = ft_substr(input, start, *i - start);
	if (word && *word)
	{
		new_token = create_token(word, WORD);
		new_token->status = DEFAULT;
		if (input[*i] == '$')
			new_token->skip_space = 1;
		add_token(tokens, new_token);
		free(word);
	}
}

static char	*extract_dollar_sequence(char *input, int *i)
{
	int		count;
	int		j;
	char	*var_name;

	count = 0;
	j = 0;
	while (input[*i + 1] == '$')
	{
		count++;
		(*i)++;
	}
	(*i)++;
	var_name = malloc(count + 2);
	if (!var_name)
		return (NULL);
	while (j < count + 1)
	{
		var_name[j] = '$';
		j++;
	}
	var_name[count + 1] = '\0';
	return (var_name);
}

static char	*extract_exit_status_var(int *i)
{
	char	*var_name;

	var_name = ft_strdup("$?");
	(*i) += 2;
	return (var_name);
}

static char	*extract_normal_var(char *input, int *i, int start)
{
	char	*var_name;

	(*i)++;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	var_name = ft_substr(input, start, *i - start);
	return (var_name);
}

void	tokenize_var(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*var_name;
	t_token	*new_token;

	start = *i;
	var_name = NULL;
	if (input[*i + 1] == '$')
		var_name = extract_dollar_sequence(input, i);
	else if (input[*i + 1] == '?')
		var_name = extract_exit_status_var(i);
	else
		var_name = extract_normal_var(input, i, start);
	if (var_name && *var_name)
	{
		new_token = create_token(var_name, ENV_VAR);
		new_token->status = DEFAULT;
		add_token(tokens, new_token);
		free(var_name);
	}
}

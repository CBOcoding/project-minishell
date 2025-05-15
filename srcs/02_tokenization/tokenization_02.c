#include "minishell.h"

static void	tokenize_pipe(int *i, t_token **tokens)
{
	t_token	*new_token;

	new_token = create_token("|", PIPE);
	add_token(tokens, new_token);
	(*i)++;
}
int	tokenize_options(char *input, int *i, t_token **tokens)
{
	if (input[*i] == '>' || input[*i] == '<')
	{
		tokenize_arrows(input, i, tokens);
		return (SUCCESS);
	}	
	else if (input[*i] == '|')
	{
		tokenize_pipe(i, tokens);
		return (SUCCESS);
	}
	return (FAILURE);
}

static t_token	*append_function(int *i)
{
	(*i) += 2;
	return (create_token(">>", APPEND));
}

static t_token	*heredoc_function(int *i)
{
	(*i) += 2;
	return (create_token("<<", HEREDOC));
}

void	tokenize_arrows(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
			new_token = append_function(i);
		else
		{
			new_token = create_token(">", REDIR_OUT);
			(*i)++;
		}
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			new_token = heredoc_function(i);
		else
		{
			new_token = create_token("<", REDIR_IN);
			(*i)++;
		}
	}
	add_token(tokens, new_token);
}

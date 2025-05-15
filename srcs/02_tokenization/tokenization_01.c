#include "minishell.h"

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

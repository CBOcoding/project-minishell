#include "minishell.h"

void	handle_no_newline_option(int *newline, int *i, t_token **token)
{
	*newline = 0;
	(*i)++;
	*token = (*token)->next;
	*token = (*token)->next;
}

int	builtin_echo(char **argv, t_token *token)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		handle_no_newline_option(&newline, &i, &token);
	else
		token = token->next;
	while (argv[i] && token)
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
		{
			if (token->skip_space > 0)
				token->skip_space--;
			else
				printf(" ");
		}
		i++;
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}

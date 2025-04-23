#include"minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (value)
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
			return (free(new_token), NULL);
	}
	else
		new_token->value = NULL;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!*tokens)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

void	free_token(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	tokens = tokens->next;
	free(tmp->value);
	free(tmp);
}

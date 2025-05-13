#include"minishell.h"

static int	error_message(t_token *current, t_token *end)
{
	if (!current->next || current->next == end
		|| (current->next->type != WORD && current->next->type != ENV_VAR))
	{
		ft_putstr_fd
		("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	if (!current->next->value || current->next->type != WORD)
	{
		ft_putstr_fd
		("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_redirection(t_token *current, t_token *end, t_cmd *cmd)
{
	if (current->type == REDIR_IN)
		cmd->infile = ft_strdup(current->next->value);
	else if (current->type == REDIR_OUT)
		cmd->outfile = ft_strdup(current->next->value);
	else if (current->type == APPEND)
	{
		cmd->outfile = ft_strdup(current->next->value);
		cmd->append = 1;
	}
	else if (current->type == HEREDOC)
	{
		if (error_message(current, end))
			return (FAILURE);
		cmd->delimiter = ft_strdup(current->next->value);
		cmd->heredoc = 1;
	}
	return (SUCCESS);
}

int	handle_redirection(t_token *current,t_cmd *cmd, t_token *prev, int *index)
{
	if ((current->type == WORD || current->type == ENV_VAR) \
			&& is_prev_not_redirection(prev))
	{
		cmd->argv[*index] = ft_strdup(current->value);
		if (!cmd->argv[*index])
			return (FAILURE);
		(*index)++;
	}
	return (SUCCESS);
}

int	fill_command_data(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*prev;
	int		arg_index;

	current = start;
	prev = NULL;
	arg_index = 0;
	while (current && current != end)
	{
		if (is_redirection(current->type))
		{
			if (error_message(current, end) == FAILURE)
				return (FAILURE);
			if (check_redirection(current, end, cmd) == FAILURE)
				return (FAILURE);
			prev = current;
			current = current->next;
		}
		if (handle_redirection(current, cmd, prev, &arg_index) == FAILURE)
			return (FAILURE);
		prev = current;
		current = current->next;
	}
	cmd->argv[arg_index] = NULL;
	return (SUCCESS);
}

#include "minishell.h"

int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || \
			type == APPEND || type == HEREDOC);
}

int	is_prev_not_redirection(t_token *prev)
{
	return (!prev || !is_redirection(prev->type));
}

static int	count_arguments(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*prev;
	int		count;

	current = start;
	prev = NULL;
	count = 0;
	while (current && current != end)
	{
		if (current->type == WORD && is_prev_not_redirection(prev))
			count++;
		prev = current;
		current = current->next;
	}
	return (count);
}

void	free_command(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->delimiter)
		free(cmd->delimiter);
	ft_memset(cmd, 0, 6);
	free(cmd);
}

t_cmd	*parsed_segment(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	arg_count = count_arguments(start, end);
	cmd->argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	ft_memset(cmd->argv, 0, (arg_count + 1) * sizeof(char *));
	if (fill_command_data(cmd, start, end) == FAILURE)
	{
		free_command(cmd);
		return (NULL);
	}
	return (cmd);
}

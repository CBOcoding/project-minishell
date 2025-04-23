#include "minishell.h"

static int	is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

static int	is_prev_not_redirection(t_token *prev)
{
	return (!prev || !is_redirection(prev->type));
}
static int	count_arguments(t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*prev;
	int	count;

	current = start;
	prev = NULL;
	count = 0;
	while (current && current != end)
	{
		if ((current->type == WORD || current->type == ENV_VAR)
			&& is_prev_not_redirection(prev))
				count++;
		prev = current;
		current = current->next;
	}
	return (count);
}

static int	fill_command_data(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*current;
	t_token	*prev;  // Track previous token manually
	int		arg_index;
	
	current = start;
	prev = NULL;
	arg_index = 0;
	while (current && current != end)
	{
		 // Handle redirections
		if (is_redirection(current->type))
		{    // Next token should be the file/delimiter
			if (!current->next || current->next == end || 
				(current->next->type != WORD && current->next->type != ENV_VAR))
					return (FAILURE);		     
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
				cmd->delimiter = ft_strdup(current->next->value);
				cmd->heredoc = 1;
			}
		     // Skip the file/delimiter token
			prev = current;
			current = current->next;
			prev = current;  // The previous of the next token will be the file token
		 }
		 // Handle command and arguments
		else if ((current->type == WORD || current->type == ENV_VAR)
					&& is_prev_not_redirection(prev))
			cmd->argv[arg_index++] = ft_strdup(current->value);
		prev = current;      // Update previous token
		current = current->next;
	}
	cmd->argv[arg_index] = NULL;
	return (SUCCESS);
}
static void	free_command(t_cmd *cmd)
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
	free(cmd);
}

t_cmd	*parsed_segment(t_token *start, t_token *end)
{
		t_cmd	*cmd;
		int		arg_count;

		cmd = create_cmd();
		// First count arguments (words that aren't part of redirections)
		arg_count = count_arguments(start, end);
		// Allocate space for arguments (+1 for NULL terminator)
		cmd->argv = malloc(sizeof(char *) * (arg_count + 1));
		if (!cmd->argv) 
			return (free(cmd), NULL);
		// Parse arguments and redirections
		if (fill_command_data(cmd, start, end) == FAILURE)
			return (free_command(cmd),NULL);
		return (cmd);
}
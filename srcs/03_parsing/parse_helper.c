#include "minishell.h"

static int is_redirection(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND || type == HEREDOC);
}

static int is_prev_not_redirection(t_token *prev)
{
	return (!prev || !is_redirection(prev->type));
}
static int count_arguments(t_token *start, t_token *end)
{
	t_token *current;
	t_token *prev;
	int count;

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
static int error_message(t_token *current, t_token *end)
{
	if (!current->next || current->next == end ||
		(current->next->type != WORD && current->next->type != ENV_VAR))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	if (!current->next->value || current->next->type != WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
static int check_redirection(t_token *current, t_token *end, t_cmd *cmd)
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
static int handle_redirection(t_token *current, t_token *end,
							  t_cmd *cmd, t_token *prev, int *index)
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
	else if ((current->type == WORD || current->type == ENV_VAR) && is_prev_not_redirection(prev))
	{
		cmd->argv[*index] = ft_strdup(current->value);
		if (!cmd->argv[*index])
			return (FAILURE);
		(*index)++;
	}
	return (SUCCESS);
}
static int fill_command_data(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token *current;
	t_token *prev;
	int arg_index;

	current = start;
	prev = NULL;
	arg_index = 0;
	while (current && current != end)
	{
		if (handle_redirection(current, end, cmd, prev, &arg_index) == FAILURE)
			return (FAILURE);
		prev = current; // Aggiorna il token precedente
		current = current->next;
	}
	cmd->argv[arg_index] = NULL;
	return (SUCCESS);
}
void free_command(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
		cmd->argv = NULL; // Previene accessi dopo la liberazione
	}
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	if (cmd->outfile)
	{
		free(cmd->outfile);
		cmd->outfile = NULL;
	}
	if (cmd->delimiter)
	{
		free(cmd->delimiter);
		cmd->delimiter = NULL;
	}
	free(cmd);
}

t_cmd *parsed_segment(t_token *start, t_token *end)
{
	t_cmd *cmd;
	int arg_count;
	int i;


	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	i = 0;
	// First count arguments (words that aren't part of redirections)
	arg_count = count_arguments(start, end);

	// Allocate space for arguments (+1 for NULL terminator)
	cmd->argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	// Inizializza tutti gli elementi di argv a NULL
	while (i <= arg_count)
		cmd->argv[i++] = NULL;
	// Parse arguments and redirections
	if (fill_command_data(cmd, start, end) == FAILURE)
	{
		// Libera tutto, compreso argv e i suoi elementi
		
	}
	return (cmd);
}

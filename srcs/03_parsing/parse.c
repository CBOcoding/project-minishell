#include "minishell.h"

static int	count_commands(t_token *token)
{
	int		count;
	t_token	*current;

	count = 1;
	current = token;
	while(current)
	{
		if (current->type == PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	if (!pipeline)
		return ;
	if (pipeline->commands)
	{
		i = 0;
		while(i < pipeline->cmd_count)
		{
			if (pipeline->commands[i])
				free_command(pipeline->commands[i]);
			i++;
		}
		free(pipeline->commands);
	}
	free(pipeline);
}
static t_token	*find_command_end(t_token *token)
{
	t_token	*current;

	current	= token;
	while (current && current->type != PIPE)
		current = current->next;
	return (current);
}

static int	parse_commands(t_token *token, t_pipeline *pipeline)
{
	t_token	*current;
	t_token	*start;
	t_token	*end;
	int		cmnd_index;

	cmnd_index = 0;
	current = token;
	while(cmnd_index < pipeline->cmd_count)
	{
		start = current;
		end = find_command_end(current);
		pipeline->commands[cmnd_index] = parsed_segment(start, end);
		if (!pipeline->commands[cmnd_index])
			{
				return (FAILURE);
			}
		cmnd_index++;
		if (end && end->type == PIPE)
			current = end->next;
		else
			current = NULL;
	}
	return (SUCCESS);
}
t_pipeline	*parse_token(t_token *token)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if(!pipeline)
		return (NULL);
	pipeline->cmd_count = count_commands(token);
	pipeline->commands = malloc(pipeline->cmd_count * sizeof(t_cmd));
	if(!pipeline->commands)
		return (free(pipeline), NULL);
	if(parse_commands(token,pipeline) == FAILURE)
		{
		free_pipeline(pipeline);
		pipeline = NULL;
		return (NULL);
		}
	return (pipeline);
}

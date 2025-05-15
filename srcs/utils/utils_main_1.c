/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:45 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:45 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	process_heredocs(t_pipeline *pipeline)
{
	t_cmd	*cmd;
	char	*line;

	while (pipeline->x_pipeline < pipeline->cmd_count)
	{
		cmd = pipeline->commands[pipeline->x_pipeline];
		if (cmd->heredoc && cmd->delimiter)
		{
			if (!cmd->argv || !cmd->argv[0])
			{
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strcmp(line, cmd->delimiter) == 0)
					{
						free(line);
						break ;
					}
					free(line);
				}
			}
		}
		pipeline->x_pipeline++;
	}
	return (SUCCESS);
}

int	execute_command_or_pipeline(t_main *main)
{
	if (!main->pipeline)
		return (CONTINUE);
	main->cmd = main->pipeline->commands[0];
	if (main->cmd && main->cmd->argv && main->cmd->argv[0]
		&& ((main->pipeline->cmd_count == 1
				&& is_builtin(main->cmd->argv[0]))
			|| (ft_strcmp(main->cmd->argv[0], "cd") == 0
				&& !main->cmd->infile
				&& !main->cmd->outfile && !main->cmd->heredoc)))
	{
		main->last_exit_status = handle_command
			(main->cmd, &main->envp_new, main->last_exit_status, main->token);
		main->should_exit_a = main->cmd->should_exit;
	}
	else
		main->last_exit_status = execute_pipeline
			(main->pipeline, main->envp_new, main->token);
	return (SUCCESS);
}

int	handle_exit_check(t_main *main)
{
	if (main->cmd && main->cmd->should_exit)
	{
		free_and_null(main);
		return (BREAK);
	}
	return (SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:10 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:10 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "echo") == SUCCESS || \
		ft_strcmp(cmd, "cd") == SUCCESS || \
		ft_strcmp(cmd, "pwd") == SUCCESS || \
		ft_strcmp(cmd, "export") == SUCCESS || \
		ft_strcmp(cmd, "unset") == SUCCESS || \
		ft_strcmp(cmd, "env") == SUCCESS || \
		ft_strcmp(cmd, "exit") == SUCCESS
	);
}

int	execute_builtin(t_cmd *cmd, char ***envp_new, \
					int exit_status, t_token *token)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv, token));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd->argv, envp_new));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd->argv, envp_new));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(cmd->argv, envp_new));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv, exit_status, cmd));
	return (1);
}

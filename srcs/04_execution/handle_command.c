#include "minishell.h"

int handle_command(t_cmd *cmd, char ***envp, int last_exit_status)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (last_exit_status);

	if (is_builtin(cmd->argv[0]))
		return execute_builtin(cmd->argv, envp, &last_exit_status);
	else
		return execute_command(cmd, *envp);
}

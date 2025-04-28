#include "minishell.h"

int	handle_command(t_cmd *cmd, char ***envp_new, int last_exit_status)

{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (last_exit_status);

	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(cmd->argv, envp_new, &last_exit_status));
	else
		return (execute_command(cmd, *envp_new));
}

/*

!(*cmd->commands) 
cmd->commands -> **
(*cmd->commands) -> * index 0
++(*cmd->commands) -> * index 1
cmd->commands[0] -> [0]

*/


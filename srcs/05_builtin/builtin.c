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

int	execute_builtin(char **argv, char ***envp_new, int exit_status, \
	int *should_exit, t_token *token)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv, token));
	if (ft_strcmp(argv[0], "cd") == 0)
		return (builtin_cd(argv));
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (builtin_pwd(argv));
	if (ft_strcmp(argv[0], "export") == 0)
		return (builtin_export(argv, envp_new));
	if (ft_strcmp(argv[0], "unset") == 0)
		return (builtin_unset(argv, envp_new));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv, envp_new));
	if (ft_strcmp(argv[0], "exit") == 0)
		return (builtin_exit(argv, exit_status, should_exit));
	return (1);
}

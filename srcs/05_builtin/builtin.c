#include "minishell.h"

// // nella mia libft ho strncmp, ma non ft_strcmp, quindi o misuriamo la len del comando o teniamo questa qui.
// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 && *s1 == *s2)
// 	{
// 		s1++;
// 		s2++;
// 	}
// 	return ((unsigned char)*s1 - (unsigned char)*s2);
// }

// Check if the command is a builtin
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (
		ft_strcmp(cmd, "echo") == SUCCESS ||
		ft_strcmp(cmd, "cd") == SUCCESS ||
		ft_strcmp(cmd, "pwd") == SUCCESS ||
		ft_strcmp(cmd, "export") == SUCCESS ||
		ft_strcmp(cmd, "unset") == SUCCESS ||
		ft_strcmp(cmd, "env") == SUCCESS ||
		ft_strcmp(cmd, "exit") == SUCCESS
	);
}

// Dispatcher
int	execute_builtin(char **argv, char ***envp_new, int exit_status, int *should_exit)
{
	// (void)exit_status; // ci serve solo per Exit builtin
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv, envp_new));
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

/*
echo: Displays a line of text.
Usage: echo [-n] [string ...]
Behavior: Prints the provided strings to standard output, separated by spaces. The -n option omits the trailing newline.​

cd: Changes the current directory.
Usage: cd [directory]
Behavior: Changes the shell's current working directory to the specified path. If no directory is provided, it defaults to the value of the HOME environment variable.

pwd: Prints the current working directory.
Usage: pwd
Behavior: Outputs the absolute pathname of the current working directory.​

export: Sets environment variables.
Usage: export [name[=value] ...]
Behavior: Marks each name to be passed to child processes in the environment. If a value is provided, it assigns that value to the variable.​

unset: Removes environment variables.
Usage: unset [name ...]
Behavior: Removes each specified variable from the shell's environment.​

env: Displays the environment variables.
Usage: env
Behavior: Prints the current environment variables.​

exit: Exits the shell.
Usage: exit [n]
Behavior: Exits the shell with a status of n. If n is omitted, the exit status is that of the last command executed.
*/

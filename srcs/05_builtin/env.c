#include "minishell.h"

int	builtin_env(char **argv, char ***envp_new)
{
	int	i;

	i = 0;
	if (argv[1] != NULL)
	{
		write(STDERR_FILENO, "env: No such file or directory\n", 31);
		return (FAILURE);
	}
	else
	{
		while ((*envp_new)[i])
		{
			printf("%s\n", (*envp_new)[i]);
			i++;
		}
		return (SUCCESS);
	}
}
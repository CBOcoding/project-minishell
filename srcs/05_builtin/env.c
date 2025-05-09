#include "minishell.h"

int	builtin_env(char **argv, char ***envp_new)
{
	int	i;

	i = 0;
	if (argv[1] != NULL)
	{
		ft_putstr_fd("env: No such file or directory\n", STDERR_FILENO);
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
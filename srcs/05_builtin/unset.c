#include "minishell.h"
//not ready
int	builtin_unset(char **argv, char ***envp_new)
{
	int	i;;

	i = 0;
	if (argv[1] == NULL)
		return (0);
	else
		while ((*envp_new)[i])
		{
			printf("%s\n", (*envp_new)[i]);
			i++;
		}
		return (0);
}
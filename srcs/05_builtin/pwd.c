#include "minishell.h"

int	builtin_pwd(char **argv)
{
	char	*path;

	(void)argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd");
		return (FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}

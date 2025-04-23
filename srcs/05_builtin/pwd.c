#include "minishell.h"

int	builtin_pwd(char **argv)
{
	char *path;

	(void)argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (0);
}

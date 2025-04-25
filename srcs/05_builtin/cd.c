#include "minishell.h"

int	builtin_cd(char **argv)
{
	char *path;

	if (argv[1] == NULL)
	{
		path = getenv("HOME"); //se non c'é argomento vai alla HOME.
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 18);
			return (FAILURE);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0) // CHDIR return 0 if the change path goes well.
	{
		perror("cd");
		return (1);
	}
	return (SUCCESS);
}

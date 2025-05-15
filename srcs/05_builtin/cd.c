#include "minishell.h"

int	builtin_cd(char **argv)
{
	char	*path;
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (FAILURE);
	}
	if (argv[1] == NULL)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (FAILURE);
		}
	}
	else
		path = argv[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (SUCCESS);
}

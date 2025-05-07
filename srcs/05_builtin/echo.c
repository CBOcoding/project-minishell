#include "minishell.h"

bool	checking_envp_new(char *str, char ***envp_new)
{
	int		i;
	char	*equal;

	i = 0;
	while ((*envp_new)[i])
	{
		equal = ft_strchr((*envp_new)[i], '=');
		if (equal && ft_strcmp(str, equal + 1) == SUCCESS)
				return (true);
		i++;
	}
	return (false);
}

int	builtin_echo(char **argv, char ***envp_new)
{
	int i;
	int newline;
	bool check;

	i = 1;
	newline = 1;
	check = checking_envp_new(argv[i + 1], envp_new);


	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	// Se non ci sono argomenti, stampa solo newline
	if (!argv[i])
	{
		if (newline)
			printf("\n");
		return (SUCCESS);
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if ((argv[i + 1] && (argv[i][0] != '\'') && (argv[i + 1][0] != '\''))
			&& (argv[i + 1] && (argv[i + 1][0] != '$')) && !check)
				printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}

#include "minishell.h"

char	*join_export_args(char **argv)
{
	char	*joined;
	char	*tmp;

	joined = ft_strdup(argv[1]);
	if (!joined)
		return (NULL);

	if (argv[2])
	{
		tmp = joined;
		joined = ft_strjoin(tmp, argv[2]);
		free(tmp);
		if (!joined)
			return (NULL);
	}
	return (joined);
}

int	replace_or_add_env(char ***envp_new, char **argv, char *key)
{
	int	position;
	char	*joined;

	position = key_exists(*envp_new, key);
	if (position < 0)
		add_env_var(envp_new, argv);
	else
	{
		free((*envp_new)[position]);
		joined = join_export_args(argv);
		if (!joined)
			return (FAILURE);
		(*envp_new)[position] = joined;
	}
	return (SUCCESS);
}

int	variable_with_equal_sign(char **argv, char ***envp_new, char *equal)
{
	char *key;

	key = ft_substr(argv[1], 0, equal - argv[1]); //crea una substr con malloc.
	if (!key) //se fallisce esce e in main va liberato tutto.
		{
			perror("export: malloc failed");
			return (FAILURE);
		}
	if (is_valid_key(key))
	{
		ft_putstr_fd("Not a valid key\n", STDERR_FILENO);
		free(key);
		return (FAILURE);
	}
	// replace_or_add_env(envp_new, argv[1], key);
	if (replace_or_add_env(envp_new, argv, key) == FAILURE)
		return (FAILURE);
	free(key);
	return (SUCCESS);
}

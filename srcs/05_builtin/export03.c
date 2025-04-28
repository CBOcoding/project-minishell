#include "minishell.h"

int	replace_or_add_env(char ***envp_new, char **argv, char *key)
{
	int		position;
	char	*new_value;

	position = key_exists(*envp_new, key);
	if (position < 0)
	{
		// Non esiste → aggiungila
		if (add_env_var(envp_new, argv[1]) != 0)
		{
			perror("export: malloc failed in add_env_var");
			return (FAILURE);
		}
	}
	position = key_exists(*envp_new, key);
	if (argv[2])
	{
		new_value = ft_strjoin(argv[1], argv[2]);
		if (!new_value)
		{
			perror("export: malloc failed in new_value");
			return (FAILURE);
		}
		free((*envp_new)[position]);
		(*envp_new)[position] = new_value;
	}
	else
	{
		new_value = ft_strdup(argv[1]);
		if (!new_value)
		{
			perror("export: malloc failed in new_value");
			return (FAILURE);
		}
		free((*envp_new)[position]);
		(*envp_new)[position] = new_value;
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
		write(STDERR_FILENO, "Not a valid key\n", 16);
		free(key);
		return (FAILURE);
	}
	replace_or_add_env(envp_new, argv, key);
	free(key);
	return (SUCCESS);
}

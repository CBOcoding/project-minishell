#include "minishell.h"

int	variable_with_equal_sign(char **argv, char ***envp_new, char *equal)
{
	char *key;

	key = ft_substr(argv[1], 0, equal - argv[1]); //crea una substr con malloc.
	if (!key) //se fallisce esce e in main va liberato tutto.
		{
			perror("export: malloc failed");
			return (FAILURE);
		}
	if (!is_valid_key(key))
	{
		write(STDERR_FILENO, "Not a valid key\n", 16);
		free(key);
		return (1);
	}
	replace_or_add_env(envp_new, argv[1], key); // funzione da scrivere
	free(key);
	return (0);
}
#include "minishell.h"

int	replace_or_add_env(char ***envp_new, char *argv, char *key)
{
	int	position;

	position = key_exists(envp_new, key);
	if (position < 0)
		add_env_var(envp_new, argv);
	else
	{
		free((*envp_new)[position]);
		(*envp_new)[position] = ft_strdup(argv);
		if (!(*envp_new)[position])
			//exit_with_free	//VA COSTRUITA
			exit(1); //VA COSTRUITA una funzione di uscita con memory clean oppure metto return (1) ma va aggiustato il codice in uscita.
	}
	return (0);
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
	if (!is_valid_key(key))
	{
		write(STDERR_FILENO, "Not a valid key\n", 16);
		free(key);
		return (1);
	}
	replace_or_add_env(envp_new, argv[1], key);
	free(key);
	return (0);
}

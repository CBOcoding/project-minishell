#include "minishell.h"
//not ready
int	builtin_unset(char **argv, char ***envp_new)
{
	int	i;;

<<<<<<< HEAD

int	remove_env_var(char ***envp_old, int position)
{
	char	**envp_new;
	int		i;
	int		j;
	int		len_envp_old;
	
	i = 0;
	j = 0;
	len_envp_old = 0;
	while ((*envp_old)[len_envp_old])
		len_envp_old++;
	envp_new = malloc(sizeof(char *) * len_envp_old);
	if (!envp_new)
		return (1);//do we want to print an error message? //se serve spazio possiamo spostare su builtin_unset il calcolo di len_envp_old.
	while (i < len_envp_old)
	{
		if (i != position)
		{
			envp_new[j] = ft_strdup((*envp_old)[i]);
			j++;
		}
		i++;
	}
	envp_new[j] = NULL;
	free_envp_old(envp_old, envp_new);
	return (0);
}

int	builtin_unset(char **argv, char ***envp_new)
{
	char	*key;
	int		position;

	key = argv[1];
	if (!is_valid_key(key))
	{
		// write(STDERR_FILENO, "Not a valid key\n", 16); //BASH non stampa nulla
		return (1);
	}
	position = key_exists(*envp_new, key);
	if (position < 0)
		return (SUCCESS); //we need to test the bash behaviour quando non trova nulla da eliminare.

	remove_env_var(envp_new, position);
	return (0);
}
=======
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
>>>>>>> 96b5a69 (Still working on export, missing one function)

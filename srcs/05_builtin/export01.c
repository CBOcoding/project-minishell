#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i  = 1;
	if (key[0] == '_' || (key[0] >= 'a' && key[0] <= 'z') || \
		(key[0] >= 'A' && key[0] <= 'Z'))
	{
		while (key[i])
		{
			if (key[i] == '_' || (key[i] >= 'a' && key[i] <= 'z') || \
				(key[i] >= 'A' && key[i] <= 'Z') || (key[i] >= '0' && key[i] <= '9'))
				{
					i++;
					continue;
				}
			else
				return(FAILURE);
		}
		return(SUCCESS);
	}
	else
		return(FAILURE);
}

int	key_exists(char **envp_new, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp_new[i]) //scorro tutto envp_new per vedere se c'e gia una key.
	{
		if(ft_strncmp(envp_new[i], key, len) == 0 && \
		(envp_new[i][len] == '=' || envp_new[i][len] == '\0')) // se la variabile esiste esce con SUCCESS, controlla che ci sia = per evitare falsi positivi, tipo PATH: PATH= vs PATH_EXTRA.
			return (i);//return la posizione della key esistente (ci serve perche usiamo la stessa funzione anche con export VAR="ciao")
		i++;
	}
	return (-1);//torniamo -1 perche ogni valore positivo (0 incluso) corrisponde alla posizione della key.
	
}

void	free_envp_old(char ***envp_old, char **envp_new)
{
	int	j;

	j = 0;
	while((*envp_old[j]))
	{
		free((*envp_old)[j]);
		j++;
	}
	free(*envp_old);
	*envp_old = envp_new;
}

int	add_env_var(char ***envp_old, char *argv)
{
	char	**envp_new;
	int		i;
	int		len_envp_old;
	char	*new_var;

	i = 0;
	len_envp_old = 0;
	while ((*envp_old)[len_envp_old])
		len_envp_old++;
	envp_new = malloc(sizeof(char *) * len_envp_old + 2);
	if (!envp_new)
		return (1);//do we want to print an error message?
<<<<<<< HEAD
=======
	i = 0;
>>>>>>> 96b5a69 (Still working on export, missing one function)
	while (i < len_envp_old)
	{
		envp_new[i] = ft_strdup((*envp_old)[i]);
		i++;
	}
	new_var = ft_strdup(argv);
	if (!new_var)
		return (1);
	envp_new[i++] = new_var;
	envp_new[i] = NULL;
<<<<<<< HEAD
	free_envp_old(envp_old, envp_new);
=======
	free_envp_old(*envp_old, envp_new);
>>>>>>> 96b5a69 (Still working on export, missing one function)
	return (0);
}

int	builtin_export(char **argv, char ***envp_new)
{
	char *equal;

	if (argv[1] == NULL)//parte 1, arriva il comando: export
		return (only_export(envp_new));
	equal = ft_strchr(argv[1], '='); //non controlla per += va giustificato dicendo che il subject non lo richiede come per esempio richiedeva -n in echo.
	if (equal) //parte 3, arriva il comando: export VAR=valore
		variable_with_equal_sign(argv, envp_new, equal);
	else //parte 2, arriva il comando: export VAR
	{
		if (!is_valid_key(argv[1]))
		{
			write(STDERR_FILENO, "Not a valid key\n", 16);
			return (1);
		}
<<<<<<< HEAD
		if (key_exists(*envp_new, argv[1]) < 0)
=======
		if (!key_exists(*envp_new, argv[1]))
>>>>>>> 96b5a69 (Still working on export, missing one function)
			if (add_env_var(envp_new, argv[1]) == 1) // aggiungi VARIABLE = vuoto
				return (1);
	}
	return (0);
}

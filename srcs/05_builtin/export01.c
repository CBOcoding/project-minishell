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
		if(ft_strncmp(envp_new[i], key, len) == 0 && envp_new[i][len] == '=') // se la variabile esiste esce con SUCCESS, controlla che ci sia = per evitare falsi positivi, tipo PATH: PATH= vs PATH_EXTRA.
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
	
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
		print_error(argv[1]);// funzione da scrivere
		free(key);
		return (1);
	}
	replace_or_add_env(envp_new, argv[1], key); // funzione da scrivere
	free(key);
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
			print_error(argv[1]);// funzione da scrivere
			return (1);
		}
		if (!key_exists(*envp_new, argv[1]))
			add_env_var(envp_new, argv[1]); // aggiungi VARIABLE = vuoto // funzione da scrivere
	}
	return (0);
}

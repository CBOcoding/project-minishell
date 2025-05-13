#include "minishell.h"

int	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (key[0] == '_' || (key[0] >= 'a' && key[0] <= 'z') || \
		(key[0] >= 'A' && key[0] <= 'Z'))
	{
		while (key[i])
		{
			if (key[i] == '_' || (key[i] >= 'a' && key[i] <= 'z') || \
				(key[i] >= 'A' && key[i] <= 'Z') || \
				(key[i] >= '0' && key[i] <= '9'))
			{
				i++;
				continue ;
			}
			else
				return (FAILURE);
		}
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	free_envp_old(char ***envp_old, char **envp_new)
{
	int	j;

	j = 0;
	while ((*envp_old)[j] != NULL)
	{
		free((*envp_old)[j]);
		j++;
	}
	free(*envp_old);
	*envp_old = envp_new;
}

int	add_env_var(char ***envp_old, char **argv)
{
	char	**envp_new;
	int		i;
	int		len_envp_old;
	char	*new_var;

	i = 0;
	len_envp_old = 0;
	while ((*envp_old)[len_envp_old])
		len_envp_old++;
	envp_new = malloc(sizeof(char *) * (len_envp_old + 2));
	if (!envp_new)
		return (FAILURE);
	while (i < len_envp_old)
	{
		envp_new[i] = ft_strdup((*envp_old)[i]);
		i++;
	}
	new_var = join_export_args(argv);
	if (!new_var)
		return (FAILURE);
	envp_new[i++] = new_var;
	envp_new[i] = NULL;
	free_envp_old(envp_old, envp_new);
	return (SUCCESS);
}

int	add_env_var2(char ***envp_old, char *argv)
{
	char	**envp_new;
	int		i;
	int		len_envp_old;
	char	*new_var;

	i = 0;
	len_envp_old = 0;
	while ((*envp_old)[len_envp_old])
		len_envp_old++;
	envp_new = malloc(sizeof(char *) * (len_envp_old + 2));
	if (!envp_new)
		return (FAILURE);
	while (i < len_envp_old)
	{
		envp_new[i] = ft_strdup((*envp_old)[i]);
		i++;
	}
	new_var = ft_strdup(argv);
	if (!new_var)
		return (FAILURE);
	envp_new[i++] = new_var;
	envp_new[i] = NULL;
	free_envp_old(envp_old, envp_new);
	return (SUCCESS);
}

int	builtin_export(char **argv, char ***envp_new)
{
	char	*equal;

	if (argv[1] == NULL)
		return (only_export(envp_new));
	equal = ft_strchr(argv[1], '=');
	if (equal)
	{
		if (variable_with_equal_sign(argv, envp_new, equal) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (is_valid_key(argv[1]))
		{
			ft_putstr_fd("Not a valid key\n", STDERR_FILENO);
			return (1);
		}
		if (key_exists(*envp_new, argv[1]) < 0)
			if (add_env_var2(envp_new, argv[1]) == 1)
				return (FAILURE);
	}
	return (SUCCESS);
}

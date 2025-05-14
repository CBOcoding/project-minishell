#include "minishell.h"

void	free_envp_new(char **envp_new)
{
	int	i;

	i = 0;
	if (!envp_new)
		return ;
	while (envp_new[i])
	{
		free(envp_new[i]);
		i++;
	}
	free(envp_new);
}

int	space_for_envp_new(char **envp, char ***envp_new)
{
	int	len;
	int	x;

	len = 0;
	x = 0;
	while (envp[len])
		len++;
	(*envp_new) = malloc(sizeof(char *) * (len + 1));
	if (!(*envp_new))
		return (FAILURE);
	while (envp[x] != NULL)
	{
		(*envp_new)[x] = ft_strdup(envp[x]);
		if (!(*envp_new)[x])
		{
			free_envp_new(*envp_new);
			return (FAILURE);
		}
		x++;
	}
	(*envp_new)[x] = NULL;
	return (SUCCESS);
}

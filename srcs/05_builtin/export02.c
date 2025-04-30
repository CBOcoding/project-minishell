#include "minishell.h"

void	array_sorting(char **sorted, int envp_len)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < envp_len - 1)
	{
		j = 0;
		while (j < envp_len - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0) //se non sono in ordine ritorna FAILURE = 1 ed entra per fare swap.
			{
				temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_sorted(char **sorted)
{
	int		i;
	char	*equal;
	int		key_len;

	i = 0;
	while (sorted[i])
	{
		printf("declare -x ");
		equal = ft_strchr(sorted[i], '='); //ritorna NULL se non trova =.
		if (!equal)
			printf("%s\n", sorted[i]);
		else
		{
			key_len = equal - sorted[i];
			//add fork for printing as a child.???
			printf("%.*s=\"%s\"\n", key_len, sorted[i], equal + 1);
		}
		i++;
	}
}

void	free_sorted(char **sorted, int envp_len)
{
	int	k;

	k = 0;
	while (k < envp_len)
	{
		free(sorted[k]);
		k++;
	}
}

int	only_export(char ***envp_new)
{
	int		i;
	int		envp_len;
	char	**sorted;

	i = 0;
	envp_len = 0;
	while ((*envp_new)[envp_len])
		envp_len++;
	sorted = malloc(sizeof(char *) * (envp_len + 1));
		if (!sorted)
		{
			perror("Malloc error");
			return (FAILURE);
		}
	while (i < envp_len)
	{
		sorted[i] = ft_strdup((*envp_new)[i]);
		if (!sorted[i])
		{
			perror("Malloc error");
			// libera già allocati
			while (--i >= 0)
				free(sorted[i]);
			free(sorted);
			return (FAILURE);
		}
		i++;
	}
	sorted[envp_len] = NULL;
	array_sorting(sorted, envp_len);
	print_sorted(sorted);
	free_sorted(sorted, envp_len);
	free(sorted);
	return (SUCCESS);
}
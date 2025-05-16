/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:26 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:26 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (FAILURE);
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
	return (SUCCESS);
}

int	builtin_unset(char **argv, char ***envp_new)
{
	char	*key;
	int		position;

	key = argv[1];
	if (is_valid_key(key))
		return (FAILURE);
	position = key_exists(*envp_new, key);
	if (position < 0)
		return (SUCCESS);
	remove_env_var(envp_new, position);
	return (SUCCESS);
}

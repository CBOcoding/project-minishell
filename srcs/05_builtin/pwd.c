/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:24 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:24 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(char **argv)
{
	char	*path;

	(void)argv;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		perror("pwd");
		return (FAILURE);
	}
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}

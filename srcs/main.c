/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:42:50 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:42:50 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_main(t_main **main, char **envp)
{
	*main = malloc(sizeof(t_main));
	if (!*main)
		return (FAILURE);
	setup_signals();
	disable_echoctl();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	ft_memset(*main, 0, sizeof(t_main));
	if (space_for_envp_new(envp, &(*main)->envp_new) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
	int		value;

	(void)argc;
	(void)argv;
	if (init_main(&main, envp) == FAILURE)
		return (FAILURE);
	main->last_exit_status = main_loop(main);
	rl_clear_history();
	free_envp_new(main->envp_new);
	value = main->last_exit_status;
	free(main);
	return (value);
}

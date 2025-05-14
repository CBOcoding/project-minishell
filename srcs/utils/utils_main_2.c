#include"minishell.h"

void	free_and_null(t_pipeline **pipeline, t_token **token, char **input)
{
	if (*pipeline)
	{
		free_pipeline(*pipeline);
		*pipeline = NULL;
	}
	if (*token)
	{
		free_token(*token);
		*token = NULL;
	}
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
}

int	prepare_pipeline(t_main *main)
{
	expand_env_vars(main->token, main->envp_new, main->last_exit_status);
	main->pipeline = parse_token(main->token);
	if (!main->pipeline)
	{
		free_and_null(&main->pipeline, &main->token, &main->input);
		return (CONTINUE);
	}
	main->cmd = main->pipeline->commands[0];
	if (process_heredocs(main->pipeline) == FAILURE)
	{
		free_and_null(&main->pipeline, &main->token, &main->input);
		return (CONTINUE);
	}
	return (SUCCESS);
}

int	execute_prompt(t_main *main)
{
	int result;

	result = prepare_pipeline(main);
	if (result != SUCCESS)
		return (result);
	execute_command_or_pipeline(main);
	return (handle_exit_check(main));
}

int	loop_check_and_prompt(char **input)
{
	g_signal = 42;
	*input = readline("minishell$ ");
	g_signal = 0;
	if (!*input)
	{
		ft_putstr_fd("exit\n", 2);
		return (BREAK);
	}
	if ((*input)[0] == '\0')
	{
		free(*input);
		return (CONTINUE);
	}
	else
		add_history(*input);
	return (SUCCESS);
}

int	main_loop(t_main *main)
{
	while (!main->should_exit_a)
	{
		main->proceed = loop_check_and_prompt(&main->input);
		if (main->proceed == BREAK)
			break ;
		if (main->proceed == CONTINUE)
			continue ;
		main->token = tokenize_input(main->input);
		if (!main->token)
			continue ;
		main->proceed = execute_prompt(main);
		if (main->proceed == BREAK)
			break ;
		if (main->proceed == CONTINUE)
			continue ;
		free_and_null(&main->pipeline, &main->token, &main->input);
	}
	return (main->last_exit_status);
}
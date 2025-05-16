#include"minishell.h"

void free_and_null(t_main *main)
{
    // Libera prima i comandi individuali
    if (main->pipeline)
    {
        free_pipeline(main->pipeline);
        main->pipeline = NULL;
        main->cmd = NULL; // Importante: anche cmd deve essere impostato a NULL
    }
    
    // Poi libera i token
    if (main->token)
    {
        free_token(main->token);
        main->token = NULL;
    }
    
    // Infine libera l'input
    if (main->input)
    {
        free(main->input);
        main->input = NULL;
    }
}

int	prepare_pipeline(t_main *main)
{
	expand_env_vars(main->token, main->envp_new, main->last_exit_status);
	main->pipeline = parse_token(main->token);
	if (!main->pipeline)
	{
		free_and_null(main);
		return (CONTINUE);
	}
	main->cmd = main->pipeline->commands[0];
	if (process_heredocs(main->pipeline) == FAILURE)
	{
		free_and_null(main);
		return (CONTINUE);
	}
	return (SUCCESS);
}
int execute_prompt(t_main *main)
{
    int result;

    result = prepare_pipeline(main);
    if (result != SUCCESS)
        return (result);

    result = execute_command_or_pipeline(main);
    
    // Importante: aggiungi controlli per verificare se ci sono heredoc
    // e se sono stati elaborati correttamente
    if (main->pipeline)
    {
        int contains_heredoc = 0;
        int i;
        
        for (i = 0; i < main->pipeline->cmd_count; i++)
        {
            if (main->pipeline->commands[i] && main->pipeline->commands[i]->heredoc)
            {
                contains_heredoc = 1;
                break;
            }
        }
        
        // Se il comando conteneva heredoc, assicurati che tutte le risorse siano liberate
        if (contains_heredoc)
        {
            // Forzare la pulizia completa
            result = handle_exit_check(main);
            free_and_null(main);
            return (result == BREAK) ? BREAK : CONTINUE;
        }
    }
    
    return handle_exit_check(main);
}

int	loop_check_and_prompt(char **input)
{
	g_signal = 42;
	*input = readline("minishell$ ");
	g_signal = 0;
	if (!*input)
	{
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
int main_loop(t_main *main)
{
    while (!main->should_exit_a)
    {
        main->proceed = loop_check_and_prompt(&main->input);
        if (main->proceed == BREAK)
            break;
        if (main->proceed == CONTINUE)
            continue;
            
        main->token = tokenize_input(main->input);
        if (!main->token)
        {
            free(main->input);
            main->input = NULL;
            continue;
        }
            
        main->proceed = execute_prompt(main);
        if (main->proceed == BREAK)
            break;
        if (main->proceed == CONTINUE)
            continue;
            
        free_and_null(main);
    }
    
    // Assicurati che tutte le risorse siano liberate prima dell'uscita
    if (main->input)
    {
        free(main->input);
        main->input = NULL;
    }
    
    if (main->token)
    {
        free_token(main->token);
        main->token = NULL;
    }
    
    if (main->pipeline)
    {
        free_pipeline(main->pipeline);
        main->pipeline = NULL;
    }
    
    return (main->last_exit_status);
}

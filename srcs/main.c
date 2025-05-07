#include "minishell.h"
#include "signals.h"
#include <termios.h>

// void	reset_terminal_settings(void);
    //se serve fare spazio per norminette, si puo mettere magari in un file con tutte le free
void	free_envp_new(char **envp_new)
{
    int i = 0;

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
    //avrei potuto usare ft_strdup che poi chiama ft_strlen
    //quindi ho preferito riscivere due righe di codice
    //cosi abbiamo tutto qua se ci sono BUG.

    int len;
    int x;

    len = 0;
    x = 0;
    while (envp[len])
        len++;
    (*envp_new) = malloc(sizeof(char *) * (len + 1));
    if (!(*envp_new))
        return (FAILURE);
    while (envp[x] != NULL) // oppure (x < len)
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

 	int	process_heredocs(t_pipeline *pipeline)
 {
 	int		i;
 	t_cmd	*cmd;
 	i = 0;
 	while (i < pipeline->cmd_count)
 	{
 		cmd = pipeline->commands[i];
 		if (cmd->heredoc && cmd->delimiter)
 		{
 			// ⚠️ esegui heredoc SOLO se il comando non esiste
 			if (!cmd->argv || !cmd->argv[0])
 			{
 				char *line;
 				while (1)
 				{
 					line = readline("> ");
 					if (!line || ft_strcmp(line, cmd->delimiter) == 0)
 					{
 						free(line);
 						break;
 					}
 					free(line); // scarta input
 				}
 			}
 		}
 		i++;
 	}
 	return (SUCCESS);
 }
	
	

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *input;
    int last_exit_status;
	int	should_exit;
	t_pipeline *pipeline = NULL;
	// t_cmd *cmd = NULL;
	t_cmd *cmd;

	(void)cmd;
    last_exit_status = 0;
	should_exit = 0;
    setup_signals();
    disable_echoctl();

    //creo qui una copia di ENVP con malloc che utilizzo nei BUILTIN perche non possiamo modificare ENVP.
    // da mettere dopo il parsing se tutto é andato a buon fine.
    //non credo che dobbiamo fare FREE per ENVP perche non abbiamo creato noi quella memoria.
    // dovremmo poi liberare ENVP_NEW che creo io.
    //chiamo una funzione esterna per chiarezza.
    char    **envp_new;
    if (space_for_envp_new(envp, &envp_new) == FAILURE)
        return (FAILURE);



		while (!should_exit) {
			//  Reset signal flag before readline
			g_signal = 0;
			input = readline("minishell$ ");
	
			if (!input) {
				//  Handle Ctrl+D (EOF)
				printf("exit\n");
				break;
			}
	
			if (g_signal == SIGINT) {
				//  readline was interrupted by Ctrl+C
				free(input); //  Free input if readline allocated memory
				input = NULL;  //  Important: set input to NULL
				continue;      //  Go to the next loop iteration, *no* prompt
			}

        // Step 2: Display the input (just to show it worked)
        // printf("You entered: %s\n", input);

        // Add command to history if it's not empty
        if (input[0] != '\0')
            add_history(input);


        // DO STUFF...
        //(void)envp; //for testing
        t_token *token = tokenize_input(input);
        if (!token)
			continue;
            // printf("No tokens generated.\n");
        else
        {
            // // Placeholder: simulate successful command result for now
            // // Later you will update this line with real execution result
            // last_exit_status = 0;// to be  removed when parsing is done.
            // //last_exit_status = execute_command(cmd, envp); //this is what is remaining when parsing is done.

            expand_env_vars(token, envp_new, last_exit_status); //rimane // Expand environment variables

            // print_tokens(token); //DEBUG da rimuovere

            // Parse tokens into command structure
        // t_cmd *cmd = parse_tokens(token); // TODO: implementare parser
		pipeline = parse_token(token);
		if (!pipeline)
		{
			free_token(token);
			free(input);
			continue;
		}

		 cmd = pipeline->commands[0];

		 // anche se argv è NULL, possiamo avere heredoc
		 if (process_heredocs(pipeline) == FAILURE)
		 {
		 	free_pipeline(pipeline);
		 	free_token(token);
		 	free(input);
		 	continue;
		 }
		
		// // se non c’è comando, non fare nulla, ma esci pulito (come bash)
		// if (!cmd || !cmd->argv || !cmd->argv[0])
		// {
		// 	free_pipeline(pipeline);
		// 	free_token(token);
		// 	free(input);
		// 	continue;
		// }
		
		

		if(pipeline)
		{
			cmd = pipeline->commands[0];

			if (cmd && cmd->argv && cmd->argv[0] && ((pipeline->cmd_count == 1 && is_builtin(cmd->argv[0]))||
			(ft_strcmp(cmd->argv[0], "cd") == 0 && !cmd->infile && !cmd->outfile && !cmd->heredoc)))
				last_exit_status = handle_command(cmd, &envp_new, last_exit_status, &should_exit);
			else
				last_exit_status = execute_pipeline(pipeline, envp_new);
			if (should_exit)
				{
					free_pipeline(pipeline);
					pipeline = NULL;
					free_token(token);
					free(input);
					break;
				}
		}

		free_pipeline(pipeline);
		pipeline = NULL;
        }
        // Free the allocated memory (tokens, cmd, etc.)
		// free_pipeline(pipeline);
		free_token(token); // Free the tokens after use
        // free(cmd); // Free the command string after use
		// free_command(cmd);
		// if (pipeline)
			// free_pipeline(pipeline);
		free(input);// Free the input string after use
    }

    // Clear the history before exiting
    rl_clear_history();
    // reset_terminal_settings();
    free_envp_new(envp_new); //creata con malloc ad inizio MAIN con "space_for_envp_new".
    return (last_exit_status);
}

// //the following is avoiding crashes of the terminal.
// void	reset_terminal_settings(void)
// {
// 	struct termios term;

// 	if (tcgetattr(STDIN_FILENO, &term) == -1)
// 		return ;
// 	term.c_lflag |= ECHOCTL;
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// }

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

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *input;
    int last_exit_status;

    last_exit_status = 0;

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



    while (1)
    {
        // Step 1: Display prompt and read input
        input = readline("minishell$ ");

        // Check if readline returned NULL (happens on Ctrl+D or EOF)
        if (!input)
        {
            printf("exit\n");
            break;
        }

        // Step 2: Display the input (just to show it worked)
        printf("You entered: %s\n", input);

        // Add command to history if it's not empty
        if (input[0] != '\0')
            add_history(input);


        // DO STUFF...
        //(void)envp; //for testing
        t_token *token = tokenize_input(input);
        if (!token)
            printf("No tokens generated.\n");
        else
        {
            // // Placeholder: simulate successful command result for now
            // // Later you will update this line with real execution result
            // last_exit_status = 0;// to be  removed when parsing is done.
            // //last_exit_status = execute_command(cmd, envp); //this is what is remaining when parsing is done.

            expand_env_vars(token, envp, last_exit_status); //rimane // Expand environment variables

            print_tokens(token); //DEBUG da rimuovere

            // Parse tokens into command structure
        // t_cmd *cmd = parse_tokens(token); // TODO: implementare parser
		t_cmd *cmd = NULL;

        // Execute the command
        last_exit_status = handle_command(cmd, &envp_new, last_exit_status);

        }
        // Free the allocated memory (tokens, cmd, etc.)
        // free_tokens(token); // Free the tokens after use
        // free(cmd); // Free the command string after use
        free(input);// Free the input string after use
    }

    // Clear the history before exiting
    rl_clear_history();
    // reset_terminal_settings();
    free_envp_new(envp_new); //creata con malloc ad inizio MAIN con "space_for_envp_new".
    return (0);
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

#include "minishell.h"
#include "signals.h"
#include <termios.h>

// void	reset_terminal_settings(void);

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;
    char *input;
    int last_exit_status;

    last_exit_status = 0;

    setup_signals();
    disable_echoctl();

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
            // Placeholder: simulate successful command result for now
            // Later you will update this line with real execution result
            last_exit_status = 0;// to be  removed when parsing is done.
            //last_exit_status = execute_command(cmd, envp); //this is what is remain when parsing is done.

            expand_env_vars(token, envp, last_exit_status); //rimane

            print_tokens(token); //DEBUG da rimuovere
        }
        // Free the allocated memory
        free(input);
    }

    // Clear the history before exiting
    rl_clear_history();
    // reset_terminal_settings();
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
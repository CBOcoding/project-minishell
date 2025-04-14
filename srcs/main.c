#include "minishell.h"
#include "signals.h"
#include <termios.h>


int main(void)
{
    char *input;

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
        t_token *token = tokenize_input(input);
        if (!token)
        printf("No tokens generated.\n");
    else
    {
        print_tokens(token);
    }
        // Free the allocated memory
        free(input);
    }
    
    // Clear the history before exiting
    rl_clear_history();
    
    return (0);
}


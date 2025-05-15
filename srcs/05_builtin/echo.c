#include "minishell.h"

void	handle_no_newline_option(int *newline, int *i, t_token **token)
{
	*newline = 0;
	(*i)++;
	*token = (*token)->next;
	*token = (*token)->next;
}

int builtin_echo(char **argv, t_token *token)
{
    int i;
    int newline;

    i = 1;
    newline = 1;
    
    // Skip the "echo" command token
    if (!token)
        return (SUCCESS);
    
    // Handle -n option
    if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
        handle_no_newline_option(&newline, &i, &token);
    else
        token = token->next;
    
    // Print arguments
    while (argv[i] && token)
    {
        ft_putstr_fd(argv[i], 1);
        
        // Add space only if there's another argument and skip_space is not set
        if (argv[i + 1])
        {
            if (!token->skip_space)
                ft_putstr_fd(" ", 1);
            else if (token->skip_space > 0)
                token->skip_space--;
        }
        
        i++;
        token = token->next;
    }
    
    if (newline)
        ft_putstr_fd("\n", 1);
    
    return (SUCCESS);
}

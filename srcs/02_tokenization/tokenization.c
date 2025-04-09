#include "minishell.h"

t_token *create_token(char *value, t_token type)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    if (value)
    {
      new_token->value = ft_strdup(value);
      if (!new_token->value)
        return (free(new_token),NULL);  
    }
    else 
        new_token->value = NULL;
    new_token->type = type;
    new_token->next = NULL;
    return (new_token);
}

void add_token(t_token **tokens, t_token *new_token)
{
    t_token *current;
    if(!*tokens)
        *tokens = new_token;
    else
    {
        current = *token;
        while (current->next)
            current = current->next;
    }    current->next = new_token;    
}
void handle_arrows(char *input, t_token **tokens)
{
    t_token *new_token;
    
    if (input[0] == '>')
    {
        if (input[1] == '>')
        {
            new_token = create_token(">>", APPEND);
            add_token(tokens, new_token);

        }
        else
        {
            new_token = create_token(">", REDIR_OUT);
            add_token(tokens, new_token);
        }
    }
    if (input[0] == '<')
    {
        if (input[1]== '<')
        {
            new_token = create_token("<<", HEREDOC);
            add_token(tokens, new_token);

        }
        else {
            new_token = create_token("<", REDIR_IN);
            add_token(tokens, new_token);
        }
    }

}

#include "minishell.h"

void tokenize_arrows(char *input, int *i, t_token **tokens) {
    t_token *new_token;
    if (input[*i] == '>') {
        if (input[*i + 1] == '>') {
            new_token = create_token(">>", APPEND);
            (*i) += 2;
        } else {
            new_token = create_token(">", REDIR_OUT);
            (*i)++;
        }
    } else if (input[*i] == '<') {
        if (input[*i + 1] == '<') {
            new_token = create_token("<<", HEREDOC);
            (*i) += 2;
        } else {
            new_token = create_token("<", REDIR_IN);
            (*i)++;
        }
    }
    add_token(tokens, new_token);
}


void tokenize_pipe(int *i, t_token **tokens) {
    t_token *new_token = create_token("|", PIPE);
    add_token(tokens, new_token);
    (*i)++;
}




void tokenize_word(char *input, int *i, t_token **tokens, t_status *status)
{
    if (*status == DEFAULT)
    {
        // Check if this is the start of a quoted section
        if (input[*i] == '\'')
        {
            *status = SQUOTE;
            tokenize_single_quote(input, i, tokens, status);
        }
        else if (input[*i] == '"')
        {
            *status = DQUOTE;
            tokenize_double_quote(input, i, tokens, status);
        }
        else if (input[*i] == '$')
        {
            tokenize_var(input, i, tokens);
        }
        else
        {
            tokenize_simple_word(input, i, tokens);
        }
    }
    else if (*status == SQUOTE)
    {
        tokenize_single_quote(input, i, tokens, status);
    }
    else if (*status == DQUOTE)
    {
        tokenize_double_quote(input, i, tokens, status);
    }
}


t_token *tokenize_input(char *input)
{
    t_token *tokens = NULL;
    t_status status = DEFAULT;
    int i = 0;

    while (input[i])
    {
        // Skip spaces outside quotes
        if (ft_isspace(input[i]) && status == DEFAULT)
        {
            i++;
            continue;
        }

        // Handle special characters outside quotes
        if (status == DEFAULT)
        {
            if (input[i] == '>' || input[i] == '<')
            {
                tokenize_arrows(input, &i, &tokens);
                continue;
            }
            else if (input[i] == '|')
            {
                tokenize_pipe(&i, &tokens);
                continue;
            }
        }
        
        // Handle words or quoted content
        tokenize_word(input, &i, &tokens, &status);
    }
    
    // Check for unclosed quotes
    if (status != DEFAULT)
    {
        printf("Error: Unclosed quotes\n");
       free_token(tokens);
        return NULL;
    }
    
    return tokens;
}




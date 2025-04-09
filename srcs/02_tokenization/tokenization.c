#include "minishell.h"

void handle_arrows(char *input, int *i, t_token **tokens)
{
    t_token *new_token;
    
    if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            new_token = create_token(">>", APPEND);
            add_token(tokens, new_token);
            (*i) += 2;
        }
        else
        {
            new_token = create_token(">", REDIR_OUT);
            add_token(tokens, new_token);
            (*i)++;
        }
    }
    else if (input[*i] == '<')
    {
        if (input[*i + 1] == '<')
        {
            new_token = create_token("<<", HEREDOC);
            add_token(tokens, new_token);
            (*i) += 2;
        }
        else
        {
            new_token = create_token("<", REDIR_IN);
            add_token(tokens, new_token);
            (*i)++;
        }
    }
}

void handle_pipe(int *index, t_token **tokens)
{
    t_token *new_token;
  
    new_token = create_token("|", PIPE);
    add_token(tokens, new_token);
    (*index)++;
}


void handle_var(char *input, int *i, t_token **tokens)
{
    t_token *new_token;
    int start;
    char *var_name;
    
    start = *i;
    (*i)++;
    while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
        (*i)++;
    var_name = ft_substr(input, start, *i - start);
    if (!var_name)
        return ;
    new_token = create_token(var_name, ENV_VAR);
    add_token(tokens, new_token); 
    free(var_name);
}

t_token *tokenize_input(char *input)
{
    t_token *tokens;
    int i;
    t_status status;

    tokens = NULL;
    status = DEFAULT;
    i = 0;
    while(input[i])
    {
        if (input[i] == '\'' && has_closed_quotes(input) == SUCCESS)
            status = SQUOTE;
        else if (input[i] == '\"' && has_closed_quotes(input) == SUCCESS)
            status = DQUOTE;
        else
            status = DEFAULT;
        if ((input[i] == '\t' || input[i] == ' ') && status == DEFAULT)
        {
            i++;
            continue;
        }
        if (status == DEFAULT)
        {
            if (input[i] == '>' || input[i] == '<')
                handle_arrows(input, &i, &tokens);
            else if (input[i] == '|')
                handle_pipe(&i, &tokens);
            else
                handle_word(input, &i, &tokens, status);
        }
        else if (status == DQUOTE)
        {
            if (input[i] == '$')
                handle_var(input, &i, &tokens);
            else
                handle_word(input, &i, &tokens, status);// TODO NOT IMPLEMENDET YET
        }
        else if (status == SQUOTE)
        {
            handle_word(input, &i, &tokens, status);// TODO NOT IMPLEMENDET YET
        }
    }
    return (tokens);
}


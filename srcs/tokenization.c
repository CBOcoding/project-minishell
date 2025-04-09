#include "minishell"

t_token *create_token(char *value, t_token type)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new)
}
void handle_arrows(char *input, t_token tokens)
{
    t_token *new_token;
    if (input == '>')
    {
        if (input 1 == '>')
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
    if (input == '<')
    {
        if (input + 1 == '<')
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

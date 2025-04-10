#include"minishell.h"

void print_tokens(t_token *token)
{
    while (token) // Process all tokens, including the last one
    {
        if (token->value)
            printf("%s ", token->value); // Print token value
        else
            printf("(null) "); // Handle null values gracefully

        switch (token->type)
        {
            case WORD:      printf("WORD - "); break;
            case PIPE:      printf("PIPE - "); break;
            case REDIR_IN:  printf("RED_IN - "); break;
            case REDIR_OUT: printf("RED_OUT - "); break;
            case APPEND:    printf("APPEND - "); break;
            case HEREDOC:   printf("HEREDOC - "); break;
            case ENV_VAR:   printf("ENV_VAR - "); break;
            default:        printf("UNKNOWN - "); break;
        }

        switch (token->status)
        {
            case DEFAULT:   printf("DEFAULT\n"); break;
            case SQUOTE:    printf("SQUOTE\n"); break;
            case DQUOTE:    printf("DQUOTE\n"); break;
        }

        token = token->next; // Move to next token
    }
}

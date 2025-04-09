#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

# include "../libraries/ft_libft/libft.h"

typedef enum e_token_type
{
    WORD,
    PIPE,
    REDIR_IN,
    REDIR_OUT,
    APPEND,
    HEREDOC,
    ENV_VAR
}   t_token_type;

typedef struct s_token {
    char *value;
    t_token_type type;
    t_status status;
    struct s_token *next;
} t_token;

typedef enum e_status
{
    DEFAULT,
    SQUOTE,
    DQUOTE
} t_status;

void	hello_minishell(void);
int ft_strcmp(const char *main, char *compared);
int has_closed_quotes(const char *str);
t_token *create_token(char *value, t_token_type type);
void add_token(t_token **tokens, t_token *new_token);
void handle_arrows(char *input, int *i, t_token **tokens);
void handle_pipe(int *index, t_token **tokens);
void handle_var(char *input, int *i, t_token **tokens);
t_token *tokenize_input(char *input);


#endif
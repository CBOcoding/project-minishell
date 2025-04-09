#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>


#include <readline/readline.h>
#include <readline/history.h>

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
    struct s_token *next;
} t_token;



void	hello_minishell(void);

#endif
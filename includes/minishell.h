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


typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ENV_VAR
}	t_token_type;

typedef enum	e_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
} t_status;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	t_status		status;
	struct s_token	*next;
} t_token;

typedef struct s_cmd
{
	int		append;        // For >> redirection
	int		heredoc;       // For << heredoc
	char	**argv;       // Command + args (e.g., ["ls", "-l", NULL])
	char	*infile;      // Input redirection file
	char	*outfile;     // Output redirection file
	char	*delimiter;   // Heredoc delimiter
} t_cmd;

typedef struct s_pipeline
{
	int		cmd_count;     // Number of commands
	t_cmd	**commands;  // Array of commands
}	t_pipeline;



int		ft_strcmp(const char *main, char *compared);
int		ft_isspace(char c);
int		has_closed_quotes(const char *str);
int		execute_command(t_cmd *cmd, char **envp);
void	hello_minishell(void);
void	add_token(t_token **tokens, t_token *new_token);
void	tokkenize_arrows(char *input, int *i, t_token **tokens);
void	tokkenize_pipe(int *index, t_token **tokens);
void	tokenize_single_quote(char *input, int *i, t_token **tokens, t_status *status);
void	tokenize_double_quote(char *input, int *i, t_token **tokens, t_status *status);
void	tokenize_simple_word(char *input, int *i, t_token **tokens);
void	tokenize_var_in_dquote(char *input, int *i, t_token **tokens);
void	tokenize_var(char *input, int *i, t_token **tokens);
void	print_tokens(t_token *token);
void	free_token(t_token *tokens);
void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status);
t_token	*tokenize_input(char *input);
t_token	*create_token(char *value, t_token_type type);
t_pipeline	*parse_token(t_token *token);
t_cmd	*parsed_segment(t_token *start, t_token *end);
t_cmd *create_cmd(void);



#endif


#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <termios.h>

# define SUCCESS 0
# define FAILURE 1

extern volatile sig_atomic_t	g_signal;

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
	int				skip_space;
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

void	free_envp_new(char **envp_new);
int		space_for_envp_new(char **envp, char ***envp_new);
int		is_prev_not_redirection(t_token *prev);
int		ft_strcmp(const char *main, const char *compared);
int		ft_isspace(char c);
int		has_closed_quotes(const char *str);
int		execute_command(t_cmd *cmd, char **envp);
int		handle_command(t_cmd *cmd, char ***envp_new, int last_exit_status, int *should_exit, t_token *token);
int		is_builtin(char *cmd);
int		execute_builtin(char **argv, char ***envp, int exit_status, int *should_exit, t_token *token);
void	add_token(t_token **tokens, t_token *new_token);
void	tokkenize_arrows(char *input, int *i, t_token **tokens);
void	tokkenize_pipe(int *index, t_token **tokens);
void	tokenize_squote(char *input, int *i, t_token **tokens, t_status *stat);
void	tokenize_dquote(char *input, int *i, t_token **tokens, t_status *stat);
void	tokenize_simple_word(char *input, int *i, t_token **tokens);
void	tokenize_var_in_dquote(char *input, int *i, t_token **tokens);
void	tokenize_var(char *input, int *i, t_token **tokens);
void	print_tokens(t_token *token);
void	free_token(t_token *tokens);
void	expand_env_vars(t_token *tokens, char **envp, int last_exit_status);
t_token	*tokenize_input(char *input);
t_token	*create_token(char *value, t_token_type type);

//execution
int	execute_pipeline(t_pipeline *pipeline, char **envp_new, t_token *token);
int	handle_heredoc(t_cmd *cmd);
size_t	ft_strspn(const char *s, const char *accept);

//builtin
int		builtin_cd(char **argv);
int		builtin_echo(char **argv, t_token *token);
int		builtin_env(char **argv, char ***envp_new);
int		builtin_export(char **argv, char ***envp_new);
int		only_export(char ***envp_new);
int		variable_with_equal_sign(char **argv, char ***envp_new, char *equal);
int		is_valid_key(char *key);
int		key_exists(char **envp_new, char *key);
int		add_env_var(char ***envp_old, char **argv);
void	free_envp_old(char ***envp_old, char **envp_new);
int		builtin_pwd(char **argv);
int		builtin_unset(char **argv, char ***envp_new);
int		builtin_exit(char **argv, int exit_status, int *should_exit);
int		is_redirection(t_token_type type);
int		is_prev_not_redirection(t_token *prev);
int		fill_command_data(t_cmd *cmd, t_token *start, t_token *end);
char	*join_export_args(char **argv);


t_pipeline	*parse_token(t_token *token);
t_cmd	*parsed_segment(t_token *start, t_token *end);
t_cmd	*create_cmd(void);
void	free_pipeline(t_pipeline *pipeline);
void	free_command(t_cmd *cmd);

//libft
int		ft_atoi(const char *nptr);
int		ft_isalnum(int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strspn(const char *s, const char *accept);
void	*ft_memset(void *s, int c, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);

//signals
void	handle_sigint(int signum);
void	handle_sigquit(int signum);
void	setup_signals(void);
void	disable_echoctl(void);


#endif


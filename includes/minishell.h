/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:40:58 by cborrome          #+#    #+#             */
/*   Updated: 2025/05/15 17:40:58 by cborrome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/wait.h>

# define SUCCESS 0
# define FAILURE 1
# define CONTINUE 2
# define BREAK 3

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	ENV_VAR
}	t_token_type;

typedef enum e_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
}	t_status;

typedef struct s_token
{
	int				skip_space;
	char			*value;
	t_token_type	type;
	t_status		status;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	int		should_exit;
	int		append;
	int		heredoc;
	char	**argv;
	char	*infile;
	char	*outfile;
	char	*delimiter;
}	t_cmd;

typedef struct s_pipeline
{
	int		x_pipeline;
	int		status;
	int		i_pipeline;
	int		cmd_count;
	t_cmd	**commands;
}	t_pipeline;

typedef struct s_main
{
	int			last_exit_status;
	int			should_exit_a;
	int			proceed;
	char		*input;
	char		**envp_new;
	t_cmd		*cmd;
	t_token		*token;
	t_pipeline	*pipeline;
}	t_main;

void		tokenize_word_dquote(char *input, int start, \
				int *i, t_token **tok);
void		handle_dquote_dollar(char *input, int *i, \
				int *start, t_token **tok);
void		check_token_spacing(char *input, int i, t_token **tok);
void		free_envp_new(char **envp_new);
void		tokenize_word(char *input, int *i, \
				t_token **tokens, t_status *status);
int			tokenize_options(char *input, int *i, t_token **tokens);
void		empty_quote_handler(char *input, int *i, t_token **delim);
int			space_for_envp_new(char **envp, char ***envp_new);
int			is_prev_not_redirection(t_token *prev);
int			ft_strcmp(const char *main, const char *compared);
int			ft_isspace(char c);
int			has_closed_quotes(const char *str);
int			execute_command(t_cmd *cmd, char **envp);
int			handle_command(t_cmd *cmd, char ***envp_new, \
				int last_exit_status, t_token *token);
int			is_builtin(char *cmd);
int			is_cmd(char c);
int			execute_builtin(t_cmd *cmd, char ***envp, \
					int exit_status, t_token *token);
void		add_token(t_token **tokens, t_token *new_token);
void		tokenize_squote(char *input, int *i, \
				t_token **tokens, t_status *stat);
void		tokenize_dquote(char *input, int *i, \
				t_token **tokens, t_status *stat);
void		tokenize_simple_word(char *input, int *i, t_token **tokens);
void		tokenize_var_in_dquote(char *input, int *i, t_token **tokens);
void		tokenize_var(char *input, int *i, t_token **tokens);
void		free_token(t_token *tokens);
void		expand_env_vars(t_token *tokens, \
				char **envp, int last_exit_status);
t_token		*tokenize_input(char *input);
t_token		*create_token(char *value, t_token_type type);
void		tokenize_arrows(char *input, int *i, t_token **tokens);
int			execute_pipeline(t_pipeline *pipeline, \
					char **envp_new, t_token *token);
int			handle_heredoc(t_cmd *cmd);
char		*find_executable(char *cmd, char **envp);
size_t		ft_strspn(const char *s, const char *accept);
int			pipeline_error(int i, t_pipeline *pipeline, int *fd);
void		pid_zero(int input_fd, int i, int *fd, t_pipeline *pipeline);
void		final_checks(int *input_fd, int i, t_pipeline *pipeline, int *fd);
int			waiting(int status);
int			fork_error(pid_t pid);
int			builtin_cd(char **argv);
int			builtin_echo(char **argv, t_token *token);
int			builtin_env(char **argv, char ***envp_new);
int			builtin_export(char **argv, char ***envp_new);
int			only_export(char ***envp_new);
int			variable_with_equal_sign(char **argv, \
				char ***envp_new, char *equal);
int			is_valid_key(char *key);
int			key_exists(char **envp_new, char *key);
int			add_env_var(char ***envp_old, char **argv);
void		free_envp_old(char ***envp_old, char **envp_new);
int			builtin_pwd(char **argv);
int			builtin_unset(char **argv, char ***envp_new);
int			builtin_exit(char **argv, int exit_status, t_cmd *cmd);
int			is_redirection(t_token_type type);
int			is_prev_not_redirection(t_token *prev);
int			fill_command_data(t_cmd *cmd, t_token *start, t_token *end);
char		*join_export_args(char **argv);
void		free_pipeline(t_pipeline *pipeline);
void		free_command(t_cmd *cmd);
t_cmd		*parsed_segment(t_token *start, t_token *end);
t_cmd		*create_cmd(void);
t_pipeline	*parse_token(t_token *token);
int			ft_atoi(const char *nptr);
int			ft_isalnum(int c);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strspn(const char *s, const char *accept);
void		*ft_memset(void *s, int c, size_t len);
char		*ft_strdup(const char *s);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
void		handle_sigint(int signum);
void		handle_sigquit(int signum);
void		setup_signals(void);
void		disable_echoctl(void);
void		free_and_null(t_main *main);
int			main_loop(t_main *main);
int			process_heredocs(t_pipeline *pipeline);
int			execute_command_or_pipeline(t_main *main);
int			handle_exit_check(t_main *main);

#endif

#include "minishell.h"

int	handle_heredoc(t_cmd *cmd)
{
	int		pipe_fd[2];
	char	*line;
	char	*delim;

	if (!cmd || !cmd->heredoc || !cmd->delimiter)
		return (-1);

	delim = ft_strdup(cmd->delimiter); // 🔒 duplica per sicurezza
	if (!delim)
		return (-1);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		free(delim);
		return (-1);
	}

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(delim);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			return (-1); // SIGINT o errore
		}
		if (strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		ft_putstr_fd( line, pipe_fd[1]);
		ft_putstr_fd( "\n", pipe_fd[1]);
		free(line);
	}

	free(delim);
	close(pipe_fd[1]);

	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc)");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}


// old version
// int handle_heredoc(t_cmd *cmd)
// {
// 	int pipe_fd[2];

// 	if (!cmd || !cmd->heredoc || !cmd->delimiter)
// 		return (-1);

// 	if (pipe(pipe_fd) == -1)
// 	{
// 		perror("pipe");
// 		return (-1);
// 	}

// 	while (1)
// 	{
// 		char *line = readline("> ");
// 		if (!line || strcmp(line, cmd->delimiter) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(pipe_fd[1], line, strlen(line));
// 		write(pipe_fd[1], "\n", 1);
// 		free(line);
// 	}

// 	close(pipe_fd[1]); // Chiudi la scrittura

// 	// Duplica nel processo figlio quando serve
// 	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 	{
// 		perror("dup2 (heredoc) failed");
// 		close(pipe_fd[0]);
// 		return (-1);
// 	}
// 	close(pipe_fd[0]);
// 	return (0);
// }

#include "minishell.h"

int	read_the_line(char *delim, int pipe_fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free(delim);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			return (-1);
		}
		if (strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	return (SUCCESS);
}

static int	open_pipe_or_cleanup(char *delim, int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		free(delim);
		return (-1);
	}
	return (0);
}

int	handle_heredoc(t_cmd *cmd)
{
	int		pipe_fd[2];
	char	*delim;

	if (!cmd || !cmd->heredoc || !cmd->delimiter)
		return (-1);
	delim = ft_strdup(cmd->delimiter);
	if (!delim)
		return (-1);
	if (open_pipe_or_cleanup(delim, pipe_fd) == -1)
		return (-1);
	if (read_the_line(delim, pipe_fd) == -1)
		return (-1);
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

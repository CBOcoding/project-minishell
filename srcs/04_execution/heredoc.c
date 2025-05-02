#include "minishell.h"
#include <readline/readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

int handle_heredoc(t_cmd *cmd)
{
	int pipe_fd[2];

	if (!cmd || !cmd->heredoc || !cmd->delimiter)
		return (-1);

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}

	while (1)
	{
		char *line = readline("> ");
		if (!line || strcmp(line, cmd->delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}

	close(pipe_fd[1]); // Chiudi la scrittura

	// Duplica nel processo figlio quando serve
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 (heredoc) failed");
		close(pipe_fd[0]);
		return (-1);
	}
	close(pipe_fd[0]);
	return (0);
}

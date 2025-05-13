#include "minishell.h"

int	pipeline_error(int i, t_pipeline *pipeline, int *fd)
{
	if (i < pipeline->cmd_count - 1)
	{
		if (pipe(fd) == -1)
		{
			perror("Fail to create a pipe");
			return (1);
		}
	}
	return (0);
}

void	pid_zero(int input_fd, int i, int *fd, t_pipeline *pipeline)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (input_fd != 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if (i < pipeline->cmd_count - 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

void	final_checks(int *input_fd, int i, t_pipeline *pipeline, int *fd)
{
	if (*input_fd != 0)
		close(*input_fd);
	if (i < pipeline->cmd_count - 1)
	{
		close(fd[1]);
		*input_fd = fd[0];
	}
}

int	waiting(int status)
{
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (status);
}

int	fork_error(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork error");
		return (1);
	}
	return (SUCCESS);
}

#include "minishell.h"

int	execute_command(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	int		infile_fd;
	int		outfile_fd;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (1);
	}
	if (pid == 0)
	{
		if (!cmd->argv[0] || ft_strspn(cmd->argv[0], " \t") == \
			ft_strlen(cmd->argv[0]))
		{
			fprintf(stderr, "minishell: command not found\n");
			exit(127);
		}
		if (cmd->infile)
		{
			infile_fd = open(cmd->infile, O_RDONLY);
			if (infile_fd < 0)
			{
				perror(cmd->infile);
				exit(1);
			}
			if (dup2(infile_fd, STDIN_FILENO) < 0)
			{
				perror("dup2 (infile)");
				close(infile_fd);
				exit(1);
			}
			close(infile_fd);
		}
		if (cmd->outfile)
		{
			int	flags = O_WRONLY | O_CREAT;
			if (cmd->append)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;

			outfile_fd = open(cmd->outfile, flags, 0644);
			if (outfile_fd < 0)
			{
				perror(cmd->outfile);
				exit(1);
			}
			if (dup2(outfile_fd, STDOUT_FILENO) < 0)
			{
				perror("dup2 (outfile)");
				close(outfile_fd);
				exit(1);
			}
			close(outfile_fd);
		}
		char *path = find_executable(cmd->argv[0], envp);
		if (path && path != cmd->argv[0])
		{
			execve(path, cmd->argv, envp);
			free(path);
		}
		else
			execve(cmd->argv[0], cmd->argv, envp);
		perror("execve");
		exit(127);
	}
	if (waitpid(pid, &status, 0) < 0)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

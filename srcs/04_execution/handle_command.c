#include "minishell.h"

int	cmd_infile(t_cmd *cmd)
{
	int	infile_fd;

	if (cmd->infile)
	{
		infile_fd = open(cmd->infile, O_RDONLY);
		if (infile_fd < 0)
		{
			perror(cmd->infile);
			return (1);
		}
		if (dup2(infile_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 (infile)");
			close(infile_fd);
			return (1);
		}
		close(infile_fd);
	}
	return (SUCCESS);
}

int	cmd_outfile(t_cmd *cmd)
{
	int	flags;
	int	outfile_fd;

	if (cmd->outfile)
	{
		flags = O_WRONLY | O_CREAT;
		if (cmd->append)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		outfile_fd = open(cmd->outfile, flags, 0644);
		if (outfile_fd < 0)
		{
			perror(cmd->outfile);
			return (1);
		}
		if (dup2(outfile_fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 (outfile)");
			close(outfile_fd);
			return (1);
		}
		close(outfile_fd);
	}
	return (SUCCESS);
}

void	backup(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
	}
}

void	cmd_infile_outfile_duplicate(t_cmd *cmd, \
			int *stdin_backup, int *stdout_backup)
{
	if (cmd->infile || cmd->outfile)
	{
		*stdin_backup = dup(STDIN_FILENO);
		*stdout_backup = dup(STDOUT_FILENO);
	}
}

int	handle_command(t_cmd *cmd, char ***envp_new, \
					int last_exit_status, t_token *token)
{
	int	stdin_backup;
	int	stdout_backup;
	int	result;

	stdin_backup = -1;
	stdout_backup = -1;
	if (!cmd || !cmd->argv || !cmd->argv[0] || \
		ft_strspn(cmd->argv[0], " \t") == ft_strlen(cmd->argv[0]))
	{
		fprintf(stderr, "minishell: command not found\n");
		return (127);
	}
	if (cmd->heredoc)
		handle_heredoc(cmd);
	cmd_infile_outfile_duplicate(cmd, &stdin_backup, &stdout_backup);
	if (cmd_infile(cmd) == 1)
		return (1);
	if (cmd_outfile(cmd) == 1)
		return (1);
	if (is_builtin(cmd->argv[0]))
		result = execute_builtin(cmd, envp_new, last_exit_status, token);
	else
		result = execute_command(cmd, *envp_new);
	backup(stdin_backup, stdout_backup);
	return (result);
}

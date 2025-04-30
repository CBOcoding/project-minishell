#include "minishell.h"
#include <fcntl.h>	  // open


	// //debug start
	// write(1, "HANDLE_COMMAND\n", 15);
	// for (int k = 0; (*envp_new)[k]; k++)
	// printf("ENVP_NEW[%i]=%s\n", k, (*envp_new)[k]);
	// //debug end

int	handle_command(t_cmd *cmd, char ***envp_new, int last_exit_status)
{
	int infile_fd;
	int outfile_fd;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (last_exit_status);

	if (cmd->heredoc)
		handle_heredoc(cmd);

	// Input redirection
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

	// Output redirection
	if (cmd->outfile)
	{
		int flags = O_WRONLY | O_CREAT;
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

	// Esecuzione del comando
	if (is_builtin(cmd->argv[0]))
		return (execute_builtin(cmd->argv, envp_new, last_exit_status));
	else
		return (execute_command(cmd, *envp_new));
	// exit(last_exit_status);
}


/*

!(*cmd->commands)
cmd->commands -> **
(*cmd->commands) -> * index 0
++(*cmd->commands) -> * index 1
cmd->commands[0] -> [0]

*/
